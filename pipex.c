/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/06/29 11:21:47 by marvin           ###   ########.fr       */
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
	//dprintf(2, "pid = %d\n", cmd->pid[cmd->index]);
	if (cmd->pid[cmd->index] < 0)
		return (dprintf(2, "pid error first cmd\n"), 0);
	if (cmd->pid[cmd->index] == 0)
	{
		//dprintf(2, "coucou first cmd\n");
		dup2(cmd->infile, 0);
		dup2(cmd->fd[1], 1);
		//close(cmd->fd[0]);
		execve(cmd->path, cmd->name, envp);
		return (dprintf(2, "execve marche pas :(\n"), 0);
		//free
	}
	else
	{
		close(cmd->fd[1]);
		close(cmd->infile);
		//waitpid(cmd->pid[cmd->index], NULL, 0);
	}
	return (1);
}

int	last_cmd(t_pipex *cmd, char **envp)
{
	//dprintf(2, "coucou last cmd\n");
	cmd->pid[cmd->index] = fork();
	//dprintf(2, "pid = %d\n", cmd->pid[cmd->index]);
	if (cmd->pid[cmd->index] < 0)
		return (dprintf(2, "pid error first cmd\n"), 0);
	if (cmd->pid[cmd->index] == 0)
	{
		
		//dprintf(2, "coucou last cmd\n");
		dup2(cmd->fd[0], 0);
		dup2(cmd->outfile, 1);
		//close(cmd->fd[1]);
		execve(cmd->path, cmd->name, envp);
		//free
		return (dprintf(2, "execve marche pas :(\n"), 0);
	}
	else
	{
		//dprintf(2, "coucoucou\n");
		close(cmd->fd[0]);
		close(cmd->outfile);
		//waitpid(cmd->pid[cmd->index], NULL, 0);
	}
	return (1);
}

int	middle_cmd(t_pipex *cmd, char **envp)
{
	cmd->pid[cmd->index] = fork();
	//dprintf(2, "pid = %d\n", cmd->pid[cmd->index]);
	if (cmd->pid[cmd->index] < 0)
		return (dprintf(2, "pid error first cmd\n"), 0);
	if (cmd->pid[cmd->index] == 0)
	{
		dup2(cmd->previous_fd, 0);
		dup2(cmd->fd[1], 1);
		//close(cmd->fd[0]);
		execve(cmd->path, cmd->name, envp);
		return (dprintf(2, "execve marche pas :(\n"), 0);
		//free
		//exit
	}
	else
	{
		close(cmd->previous_fd);
		close(cmd->fd[1]);
		//waitpid(cmd->pid[cmd->index], NULL, 0);
	}
	return(1);
}



int	pipex(char *first_arg, char *last_arg, t_pipex *cmd,char **envp)
{
	if (cmd->index == cmd->first)
	{
		open_infile(cmd, first_arg);
		open_outfile(cmd, last_arg);
		pipe(cmd->fd);
		//dprintf(2, "coucou la\n");
		//dprintf(2, "fd[0] = %d\nfd[1] = %d\n", cmd->fd[0], cmd->fd[1]);
		if (first_cmd(cmd, envp) == 0)
			return (0);
		//close(cmd->infile);
		//dprintf(2, "coucouc first cmd");
	}
	else if (cmd->index == cmd->last)
	{
		//dprintf(2, "last cmd fd[0] = %d\nfd[1] = %d\n", cmd->fd[0], cmd->fd[1]);
		//open_outfile(cmd, last_arg);
		if (last_cmd(cmd, envp) == 0)
			return (0);
		//close(cmd->fd[0]);
		//close(cmd->outfile);
		//dprintf(2, "coucou last cmd");
	}
	else if ((cmd->index != cmd->first) || (cmd->index != cmd->last))
	{
		cmd->previous_fd = cmd->fd[0];
		close(cmd->fd[1]);
		pipe(cmd->fd);
		if (middle_cmd(cmd, envp) == 0)
			return (0);
		//close(cmd->previous_fd);
		//dprintf(2, "coucou middle cmd");
	}
	return (1);
}

int	open_infile(t_pipex *cmd, char *first_arg)
{
	//dprintf(2, "first_arg = %s\n", first_arg);
	cmd->infile = open(first_arg, O_RDONLY);
	//dprintf(2, "infile = %d\n", cmd->infile);
	if (cmd->infile == -1)
	{
		dprintf(2, "coucou infile\n");
		return (0);
	}
	return (1);
}

int	open_outfile(t_pipex *cmd, char *last_arg)
{
	//dprintf(2, "coucouc outfile\n");
	cmd->outfile = open(last_arg, O_WRONLY);
	//dprintf(2, "last arg = %s\n", last_arg);
	//dprintf(2, "outfile here = %d\n", cmd->outfile);
	if (cmd->outfile == -1)
	{
		//pipex.outfile = open(av[3], O_CREAT, S_IWUSR);
		cmd->outfile = open(last_arg, O_CREAT, S_IRWXU);
		if ( cmd->outfile == -1)
			return (dprintf(2, "outfile create error\n"), 0);
		//dprintf(2, "last arg = %s\n", last_arg);
		//dprintf(2, "outfile = %d\n", cmd->outfile);
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
	//int		status;
	int		i;
	
	if (ac < 5)
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
		if (check_command(av[i], envp, &cmd) == 0)
			return (dprintf(2, "check_command error\n"), 0);
		//dprintf(2, "cmd.nbr = %d\n", cmd.nbr);
		//dprintf(2, "cmd.index = %d\n", cmd.index);
		//dprintf(2, "i = %d\n", i);
		//dprintf(2, "cmd path = %s\ncmd name = %s\n", cmd.path, cmd.name[0]);
		//dprintf(2, "av[i] = %s\n", av[i]);
		
		pipex(av[1], av[ac - 1], &cmd, envp);
		i++;
		cmd.index--;
		//dprintf(2, "cmd.index  apres = %d\n", cmd.index);
	}
	//dprintf(2, "i = %d\n", i);
	i = i - 2;
	//dprintf(2, "i = %d\n", i);
	while (i > 0)
	{
		
		waitpid(cmd.pid[i], NULL, 0);
		i--;
		//dprintf(2, "i = %d\n", i);
		//dprintf(2, "pid = %d\n", cmd.pid[i]);
	}
	//waitpid(-1, NULL, 0);
}
j