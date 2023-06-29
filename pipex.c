/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/06/29 13:03:09 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_cmd(t_pipex *cmd, char **envp)
{
	cmd->pid[cmd->index] = fork();
	if (cmd->pid[cmd->index] < 0)
		return (dprintf(2, "pid error first cmd\n"), 0);
	if (cmd->pid[cmd->index] == 0)
	{
		//dprintf(2, "coucou first cmd\n");
		dup2(cmd->infile, 0);
		dup2(cmd->fd[1], 1);
		close(cmd->fd[0]);
		execve(cmd->path, cmd->name, envp);
		//free
		return (dprintf(2, "execve marche pas :(\n"), 0);
	}
	else
	{
		close(cmd->fd[1]);
		close(cmd->infile);
	}
	return (1);
}

int	middle_cmd(t_pipex *cmd, char **envp)
{
	cmd->pid[cmd->index] = fork();
	if (cmd->pid[cmd->index] < 0)
		return (dprintf(2, "pid error first cmd\n"), 0);
	if (cmd->pid[cmd->index] == 0)
	{
		dup2(cmd->previous_fd, 0);
		dup2(cmd->fd[1], 1);
		//close(cmd->fd[0]);
		execve(cmd->path, cmd->name, envp);
		//free
		//exit
		return (dprintf(2, "execve marche pas :(\n"), 0);
	}
	else
	{
		close(cmd->previous_fd);
		close(cmd->fd[1]);
	}
	return(1);
}

int	last_cmd(t_pipex *cmd, char **envp)
{
	cmd->pid[cmd->index] = fork();
	if (cmd->pid[cmd->index] < 0)
		return (dprintf(2, "pid error first cmd\n"), 0);
	if (cmd->pid[cmd->index] == 0)
	{
		//dprintf(2, "coucou last cmd\n");
		dup2(cmd->fd[0], 0);
		dup2(cmd->outfile, 1);
		close(cmd->fd[1]);
		execve(cmd->path, cmd->name, envp);
		//free
		return (dprintf(2, "execve marche pas :(\n"), 0);
	}
	else
	{
		close(cmd->fd[0]);
		close(cmd->outfile);
	}
	return (1);
}

int	pipex(char *first_arg, char *last_arg, t_pipex *cmd,char **envp)
{
	if (cmd->index == cmd->first)
	{

		pipe(cmd->fd);
		if (first_cmd(cmd, envp) == 0)
			return (0);
	}
	else if (cmd->index == cmd->last)
	{
		if (last_cmd(cmd, envp) == 0)
			return (0);
	}
	else if ((cmd->index != cmd->first) || (cmd->index != cmd->last))
	{
		cmd->previous_fd = cmd->fd[0];
		close(cmd->fd[1]);
		pipe(cmd->fd);
		if (middle_cmd(cmd, envp) == 0)
			return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	cmd;
	int		i;
	
	if (ac < 5)
		return (0);
	open_infile(&cmd, av[1]);
	open_outfile(&cmd, av[ac - 1]);
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
			return (0);
		//dprintf(2, "cmd.nbr = %d\n", cmd.nbr);
		//dprintf(2, "cmd.index = %d\n", cmd.index);
		//dprintf(2, "i = %d\n", i);
		//dprintf(2, "cmd path = %s\ncmd name = %s\n", cmd.path, cmd.name[0]);
		//dprintf(2, "av[i] = %s\n", av[i]);
		pipex(av[1], av[ac - 1], &cmd, envp);
		i++;
		cmd.index--;
	}
	i = i - 2;
	while (i > 0)
	{
			
		waitpid(cmd.pid[i], NULL, 0);
		i--;
		//dprintf(2, "i = %d\n", i);
		//dprintf(2, "pid = %d\n", cmd.pid[i]);
	}
}
