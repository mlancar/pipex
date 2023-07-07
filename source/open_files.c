/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:13:28 by malancar          #+#    #+#             */
/*   Updated: 2023/07/07 19:23:51 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc(char *limiter, t_pipex *cmd, char **envp)
{
	char	*read_line;

	if (pipe(cmd->fd) == 0)
		free_and_exit("pipe", cmd);
	cmd->pid = fork();
	if (cmd->pid < 0)
		free_and_exit("fork", cmd);
	else if (cmd->pid == 0)
	{
		if ((dup2(cmd->here_doc, 0) != -1) && (dup2(cmd->fd[1], 1) !=-1 ))
		{
			close(cmd->fd[0]);
			while (ft_strcmp(read_line, limiter) != 0)
			{
				read_line = get_next_line(cmd->here_doc);
			}
			if (execve(cmd->path, cmd->name, envp))
				free_and_exit("execve", cmd);
		}
		else
			free_and_exit("dup2", cmd);
	}
	else
	{
		close(cmd->fd[1]);
		close(cmd->here_doc);
	}
	
}

int	open_here_doc(t_pipex *cmd, char *first_arg)
{
		cmd->here_doc = open(first_arg, O_RDONLY);
		if (cmd->here_doc == -1)
		{
			cmd->here_doc = open(first_arg, O_CREAT, S_IRWXU);
				if (cmd->here_doc == -1)
				{
						
				}
		}
		return (1);
}

int	open_infile(t_pipex *cmd, char *first_arg)
{
	cmd->infile = open(first_arg, O_RDONLY);
	if (cmd->infile == -1)
		perror("open");
	return (1);
}

int	open_outfile(t_pipex *cmd, char *last_arg)
{
	cmd->outfile = open(last_arg, O_WRONLY);
	if (cmd->outfile == -1)
	{
		//pipex.outfile = open(av[3], O_CREAT, S_IWUSR);
		cmd->outfile = open(last_arg, O_CREAT, S_IRWXU);
		if ( cmd->outfile == -1)
			return (dprintf(2, "outfile create error\n"), 0);
		if (cmd->outfile == 1)
		{
			close(cmd->outfile);
			return (0);
		}
	}
	return (1);
}