/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/06/27 01:03:08 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error(void)
{
	printf("error");
	return (0);
}

int	first_cmd(t_pipex *cmd, char **envp)
{
	cmd->pid[cmd->index] = fork();
	if (cmd->pid < 0)
		ft_error();
	if (cmd->pid == 0)
	{
		dup2(cmd->infile, 0);
		dup2(cmd->fd[1], 1);
		close(cmd->fd[0]);
		execve(cmd->path, cmd->name, envp);
		printf("execve marche pas :(\n");
		//free
	}
	return (0);
}

int	last_cmd(t_pipex *cmd, char **envp)
{
	cmd->pid[cmd->index] = fork();
	if (cmd->pid < 0)
		ft_error();
	if (cmd->pid == 0)
	{
		dup2(cmd->fd[0], 0);
		dup2(cmd->outfile, 1);
		close(cmd->fd[1]);
		execve(cmd->path, cmd->name, envp);
		printf("execve marche pas :(\n");
		//free
	}
	return (0);
}

int	middle_cmd(t_pipex *cmd, char **envp)
{
	cmd->pid[cmd->index] = fork();
	if (cmd->pid < 0)
		ft_error();
	if (cmd->pid == 0)
	{
		dup2(cmd->previous_fd, 0);
		dup2(cmd->fd[1], 1);
		close(cmd->fd[0]);
		execve(cmd->path, cmd->name, envp);
		printf("execve marche pas :(\n");
		//free
		//exit
	}
	return(0);
}



int	pipex(char *arg, t_pipex *cmd,char **envp)
{
	if (cmd->index == cmd->first)
	{
		open_infile(cmd, arg);
		pipe(cmd->fd);
		if (first_cmd(cmd, envp) == 0)
			return (0);
		close(cmd->infile);
		dprintf(2, "coucouc first cmd");
	}
	else if (cmd->index == cmd->last)
	{
		open_outfile(cmd, arg);
		if (last_cmd(cmd, envp) == 0)
			return (0);
		close(cmd->fd[0]);
		close(cmd->outfile);
		dprintf(2, "coucou last cmd");
	}
	else
	{
		cmd->previous_fd = cmd->fd[0];
		close(cmd->fd[1]);
		pipe(cmd->fd);
		if (middle_cmd(cmd, envp) == 0)
			return (0);
		close(cmd->previous_fd);
		dprintf(2, "coucou middle cmd");
	}
	return (1);
}

int	open_infile(t_pipex *cmd, char *first_arg)
{
	cmd->infile = open(first_arg, O_RDONLY);
	if (cmd->infile == -1)
	{
		dprintf(2, "coucou infile");
		return (0);
	}
	return (1);
}

int	open_outfile(t_pipex *cmd, char *last_arg)
{
	cmd->outfile = open(last_arg, O_WRONLY);
	if (cmd->outfile == -1)
	{
		//pipex.outfile = open(av[3], O_CREAT, S_IWUSR);
		cmd->outfile = open(last_arg, O_CREAT, S_IRWXU);
		dprintf(2, "outfile = %d\n", cmd->outfile);
		if (cmd->outfile == 1)
		{
			close(cmd->outfile);
			return (0);
		}
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	cmd;
	int		status;
	int		i;

	if (ac > 5)
		return (0);
	cmd.nbr = ac - 3;
	cmd.index = cmd.nbr;
	cmd.first = cmd.nbr;
	cmd.last = 1;
	i = 2;
	cmd.pid = malloc(sizeof(int) * cmd.nbr);
	if (!cmd.pid)
		return (printf("pid error"), 0);
	while (cmd.index > 0)
	{
		dprintf(2, "cmd = %s\n", av[i]);
		dprintf(2, "cmd.nbr = %d\n", cmd.nbr);
		dprintf(2, "cmd.index = %d\n", cmd.index);
		dprintf(2, "i = %d\n", i);
		pipex(av[i], &cmd, envp);
		i++;
		cmd.index--;
	}
	//dprintf(2, "i = %d\n", i);
	int j = i - 1;
	while (j > 0)
	{
		waitpid(cmd.pid[j], &status, 0);
		j--;
	}
}
