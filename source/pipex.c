/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/07/12 20:50:46 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child(int fd_in, int fd_out, int fd_other, t_pipex *cmd)
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
	return (1);
}

int	here_doc(char *limiter, t_pipex *cmd)
{
	char	*read_line;
	int		len_limiter;
	//char	file_name[7];
	//int	fd;

	len_limiter = ft_strlen(limiter);
	read_line = NULL;
	cmd->fd_tmp = 0;
	cmd->fd_tmp = open_and_fill_here_doc(cmd, limiter);
	close(cmd->fd_tmp);
	cmd->fd_tmp = open("./tmp", O_RDONLY);
	if (cmd->fd_tmp == -1)
		free_and_exit("open", cmd);
	return (1);
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
		{
			if (cmd->if_here_doc == 1)
			{
				if ((here_doc(av[2], cmd) != 1) && (child(cmd->fd_tmp, cmd->fd[1], cmd->fd[0], cmd) != 1))
					free_and_exit("command fail", cmd);
				unlink("cmd->fd_tmp");
			}
			else if (child(cmd->infile, cmd->fd[1], cmd->fd[0], cmd) != 1)
				free_and_exit("command fail first cmd", cmd);
		}
		else if ((cmd->index_pid == cmd->last) && (child(cmd->fd[0], cmd->outfile, cmd->fd[1], cmd) != 1))
			free_and_exit("command fail last cmd", cmd);
		else if ((cmd->index_pid != cmd->first) && (cmd->index_pid != cmd->last))
		{
			cmd->previous_fd = cmd->fd[0];
			if (pipe(cmd->fd) == -1)
				free_and_exit("pipe", cmd);
			if (child(cmd->previous_fd, cmd->fd[1], cmd->fd[0], cmd) == 0)
				free_and_exit("command fail middle cmd", cmd);
		}
		cmd->index++;
		cmd->index_pid++;
		free_tab(cmd->name);
		free(cmd->path);
	}
}
