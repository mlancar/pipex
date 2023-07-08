/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/07/08 20:18:17 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc(char *limiter, t_pipex *cmd, char **envp)
{
	char	*read_line;
	int		len_limiter;
	char	file_name[8];
	int	fd;


	len_limiter = ft_strlen(limiter);
	read_line = NULL;
	fd = open("/dev/random", O_RDONLY);//proteger
	if (fd == -1)
		perror("open");
	if (read(fd, file_name, 7) == -1)
	{
		perror("read");
		
	}//close
	close(fd);
	fd = open(file_name, O_CREAT, S_IRWXU);//proteger
	if (fd == -1)
		perror("open");
	read_line = get_next_line(0);
	while (ft_strncmp(limiter, read_line, len_limiter) != 0)
	{
		read_line = get_next_line(0);
		ft_putstr_fd(read_line, fd);
	}
	if (pipe(cmd->fd) == -1)
		free_and_exit("pipe", cmd);
	cmd->pid[cmd->index] = fork();
	if (cmd->pid < 0)
		free_and_exit("fork", cmd);
	else if (cmd->pid == 0)
	{
		if ((dup2(cmd->fd[1], 1) != -1) && (dup2(fd, 0) != -1))
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
		close(fd);
	}
	return (1);
}

int	first_cmd(t_pipex *cmd, char **envp)
{
	dprintf(2, "coucou first cmd\n");
	cmd->pid[cmd->index - 1] = fork();
	if (cmd->pid[cmd->index - 1] < 0)
		free_and_exit("fork", cmd);
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
	dprintf(2, "coucou middle cmd\n");
	cmd->pid[cmd->index - 1] = fork();
	if (cmd->pid[cmd->index - 1] < 0)
		free_and_exit("fork", cmd);
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
	dprintf(2, "coucou last cmd\n");
	cmd->pid[cmd->index - 1] = fork();
	if (cmd->pid[cmd->index - 1] < 0)
		free_and_exit("fork", cmd);
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

	if (cmd->if_here_doc == 1)
		i = 3;
	else
		i = 2;
	if (pipe(cmd->fd) == -1)
		free_and_exit("pipe", cmd);
	while (cmd->index <= cmd->max)
	{
		// dprintf(2, "cmd.max = %d\n", cmd->max);
		// dprintf(2, "cmd->first = %d\n", cmd->first);
		// dprintf(2, "cmd->last = %d\n", cmd->last);
		// dprintf(2, "i = %d\n", i);
		// dprintf(2, "cmd->index = %d\n", cmd->index);
		if (check_command(av[i], envp, cmd) == 0)
			write(2, "command not found\n", 18);
		else if (cmd->index == cmd->first)
		{
			if (cmd->if_here_doc == 1)
			{
					dprintf(2, "coucou heredoc\n");
				if (here_doc(av[2], cmd, envp) != 1)
					free_and_exit("command fail", cmd);
			}
			else if (first_cmd(cmd, envp) != 1)
				free_and_exit("command fail", cmd);
			
		}
		else if ((cmd->index == cmd->last) && (last_cmd(cmd, envp) != 1))
			free_and_exit("command fail", cmd);
		else if ((cmd->index != cmd->first) && (cmd->index != cmd->last))
		{
			cmd->previous_fd = cmd->fd[0];
			if (pipe(cmd->fd) == -1)
				free_and_exit("pipe", cmd);
			if (middle_cmd(cmd, envp) == 0)
				free_and_exit("command fail\n", cmd);
		}
		dprintf(2, "\n");
		i++;
		cmd->index++;
		
		free_tab(cmd->name);
		free(cmd->path);
	}
}
