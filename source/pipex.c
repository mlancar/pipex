/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/07/13 18:32:36 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(int fd_in, int fd_out, int fd_other, t_pipex *cmd)
{
	cmd->pid[cmd->index_pid - 1] = fork();
	if (cmd->pid[cmd->index_pid - 1] < 0)
		free_and_exit("fork", cmd);
	if (cmd->pid[cmd->index_pid - 1] == 0)
	{
		if ((dup2(fd_in, 0) != -1) && (dup2(fd_out, 1) != -1))
		{
			if (cmd->index_pid != cmd->last)
				close(fd_other);
			if (execve(cmd->path, cmd->name, cmd->envp))
				free_and_exit("execve", cmd);
		}
		else
			free_and_exit("dup2", cmd);
	}
	else
	{
		close(fd_in);
		close(fd_out);
	}
}

void	here_doc(char *limiter, t_pipex *cmd)
{
	cmd->fd_tmp = 0;
	open_and_fill_here_doc(cmd, limiter);
	cmd->fd_tmp = open(cmd->rand_name, O_RDONLY);
	if (cmd->fd_tmp == -1)
		free_and_exit("open", cmd);
}

void	first_cmd(char *av, t_pipex *cmd)
{
	if (cmd->if_here_doc == 1)
	{
		here_doc(av, cmd);
		exec_cmd(cmd->fd_tmp, cmd->fd[1], cmd->fd[0], cmd);
	}
	else
		exec_cmd(cmd->infile, cmd->fd[1], cmd->fd[0], cmd);
}

void	pipex(t_pipex *cmd, char **av)
{
	if (pipe(cmd->fd) == -1)
		free_and_exit("pipe", cmd);
	while (cmd->index_pid <= cmd->max)
	{
		if (check_command(av[cmd->index], cmd) == 0)
			write(2, "command not found\n", 18);
		else if (cmd->index_pid == cmd->first)
			first_cmd(av[2], cmd);
		else if (cmd->index_pid == cmd->last)
			exec_cmd(cmd->fd[0], cmd->outfile, cmd->fd[1], cmd);
		else if ((cmd->index_pid != cmd->first)
			&& (cmd->index_pid != cmd->last))
		{
			cmd->previous_fd = cmd->fd[0];
			if (pipe(cmd->fd) == -1)
				free_and_exit("pipe", cmd);
			exec_cmd(cmd->previous_fd, cmd->fd[1], cmd->fd[0], cmd);
		}
		cmd->index++;
		cmd->index_pid++;
		free_tab(cmd->name);
		free(cmd->path);
	}
}
