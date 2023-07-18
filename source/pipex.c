/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/07/18 14:11:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(int fd_in, int fd_out, int fd_other, t_pipex *cmd)
{
	dprintf(2, "cmd infile = %d\n", cmd->infile);
	dprintf(2, "cmd->outfile = %d\n", cmd->outfile);
	dprintf(2, "fd[0] = %d\n", cmd->fd[0]);
	dprintf(2, "fd[1] = %d\n", cmd->fd[1]);
	dprintf(2, "fd_in = %d\n", fd_in);
	dprintf(2, "fd_out = %d\n", fd_out);
	dprintf(2, "fd_other = %d\n", fd_other);
	cmd->pid[cmd->index_pid - 1] = fork();
	if (cmd->pid[cmd->index_pid - 1] < 0)
		free_and_exit("fork", cmd);
	else if (cmd->pid[cmd->index_pid - 1] == 0)
	{
		if (check_command(cmd->argv[cmd->index], cmd) == 0)
		{
			write(2, "command not found\n", 18);
			error_cmd(127, cmd);
		}
		else if ((dup2(fd_in, 0) != -1) && (dup2(fd_out, 1) != -1))
		{
			if ((cmd->index_pid != cmd->last))
				close(fd_other);
			if (execve(cmd->path, cmd->name, cmd->envp))
				error_cmd(0, cmd);
		}
		else
		{
			dprintf(2, "index = %d cc\n", cmd->index);
			error_cmd(0, cmd);
		}
	}
	else
	{
		if ((fd_in >= 0) && (close(fd_in) == -1))
			dprintf(2, "error close fd_in\n");
		dprintf(2, "errno = %d\n\n", errno);
		if ((fd_out >= 0) && (close(fd_out) == -1))
			dprintf(2, "error close fd_out\n");
		dprintf(2, "errno = %d\n\n", errno);
		
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

void	first_cmd(t_pipex *cmd)
{
	if (cmd->if_here_doc == 1)
	{
		here_doc(cmd->argv[2], cmd);
		exec_cmd(cmd->fd_tmp, cmd->fd[1], cmd->fd[0], cmd);
		unlink(cmd->rand_name);
	}
	else 
		exec_cmd(cmd->infile, cmd->fd[1], cmd->fd[0], cmd);
		
}

void	pipex(t_pipex *cmd)
{
	if (pipe(cmd->fd) == -1)
		free_and_exit("pipe", cmd);
	while (cmd->index_pid <= cmd->max)
	{
		dprintf(2, "cmd->index_pid = %d\n", cmd->index_pid);
		dprintf(2, "cmd->index = %d\n", cmd->index);
		if (cmd->index_pid == cmd->first)
			first_cmd(cmd);
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
	}
}
