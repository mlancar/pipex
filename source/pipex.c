/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/07/05 17:45:12 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_cmd(t_pipex *cmd, char **envp)
{
	cmd->pid[cmd->index - 1] = fork();
	if (cmd->pid[cmd->index - 1] < 0)
		return (dprintf(2, "pid error first cmd\n"), 0);//freepid
	if (cmd->pid[cmd->index - 1] == 0)
	{
		if ((dup2(cmd->infile, 0) != -1) && (dup2(cmd->fd[1], 1) != -1))
		{
			close(cmd->fd[0]);
			if (execve(cmd->path, cmd->name, envp))
				free_and_exit("execve", cmd);
		}
		else
			free_and_exit("dup2", cmd);
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
	cmd->pid[cmd->index - 1] = fork();
	if (cmd->pid[cmd->index - 1] < 0)
		return (dprintf(2, "pid error first cmd\n"), 0);//free pid
	if (cmd->pid[cmd->index - 1] == 0)
	{
		if ((dup2(cmd->previous_fd, 0) != -1) && (dup2(cmd->fd[1], 1) != -1))
		{
			close(cmd->fd[0]);
			if (execve(cmd->path, cmd->name, envp))
				free_and_exit("execve", cmd);
		}
		else
			free_and_exit("dup2", cmd);
	}
	else
	{
		close(cmd->previous_fd);
		close(cmd->fd[1]);
	}
	return (1);
}

int	last_cmd(t_pipex *cmd, char **envp)
{
	cmd->pid[cmd->index - 1] = fork();
	if (cmd->pid[cmd->index - 1] < 0)
		return (dprintf(2, "pid error first cmd\n"), 0);
	if (cmd->pid[cmd->index - 1] == 0)
	{
		if ((dup2(cmd->fd[0], 0) != -1) && (dup2(cmd->outfile, 1) != -1))
		{
			if (execve(cmd->path, cmd->name, envp))
				free_and_exit("execve", cmd);
		}
		else
			free_and_exit("dup2", cmd);
	}
	else
	{	
		close(cmd->fd[0]);
		close(cmd->outfile);
	}
	return (1);
}

void	pipex(t_pipex *cmd, char **av, char **envp)
{
	int	i;

	i = 2;
	if (pipe(cmd->fd) == -1)
		free_and_exit("pipe", cmd);
	while (cmd->index <= cmd->max)
	{
		if (check_command(av[i], envp, cmd) == 0)
			write(2, "command not found\n", 18);
		else if ((cmd->index == cmd->first) && (first_cmd(cmd, envp) != 1))
			free_and_exit("command fail", cmd);
		else if ((cmd->index == cmd->last) && (last_cmd(cmd, envp) != 1))
			free_and_exit("command fail", cmd);
		else if ((cmd->index != cmd->first) && (cmd->index != cmd->last))
		{
			dprintf(2, "coucou ici\n");
			cmd->previous_fd = cmd->fd[0];
			pipe(cmd->fd);
			if (pipe(cmd->fd) == -1)
				free_and_exit("pipe", cmd);
			if (middle_cmd(cmd, envp) == 0)
				free_and_exit("command fail\n", cmd);
		}
		i++;
		cmd->index++;
		free_tab(cmd->name);
		free(cmd->path);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	cmd;
	int		i;
	int		status;

	if (ac < 5)
		return (0);
	//if (check_here_doc() == 1);
	//	here_doc();
	open_infile(&cmd, av[1]);
	open_outfile(&cmd, av[ac - 1]);
	cmd.max = ac - 3;
	cmd.index = 1;
	cmd.first = 1;
	cmd.last = cmd.max;
	i = 0;
	cmd.pid = malloc(sizeof(pid_t) * cmd.max);
	if (!cmd.pid)
		return (printf("pid error"), 0);
	pipex(&cmd, av, envp);
	while (i > 0)
	{	
		waitpid(cmd.pid[i], &status, 0);
		i--;
	}
	free(cmd.pid);
}
