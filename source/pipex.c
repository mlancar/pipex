/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/07/16 21:43:17 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(int fd_in, int fd_out, int fd_other, t_pipex *cmd)
{
	dprintf(2, "cc\n");
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
			if ((cmd->index_pid != cmd->last) || (cmd->infile != -1))
				close(fd_other);
			if (execve(cmd->path, cmd->name, cmd->envp))
				error_cmd(0, cmd);
		}
		else
			free_and_exit("dup2", cmd);
	}
	else
	{
		dprintf(2, "cc close\n");
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

void	first_cmd(t_pipex *cmd)
{
	if (cmd->if_here_doc == 1)
	{
		here_doc(cmd->argv[2], cmd);
		exec_cmd(cmd->fd_tmp, cmd->fd[1], cmd->fd[0], cmd);
		unlink(cmd->rand_name);
	}
	else
	{
		if (cmd->infile == -1)
			exec_cmd(cmd->fd[0], cmd->fd[1], cmd->fd[0], cmd);
		else 
			exec_cmd(cmd->infile, cmd->fd[1], cmd->fd[0], cmd);
	}
		
}

void	pipex(t_pipex *cmd)
{
	if (pipe(cmd->fd) == -1)
		free_and_exit("pipe", cmd);
	while (cmd->index_pid <= cmd->max)
	{
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
