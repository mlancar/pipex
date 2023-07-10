/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/07/09 23:39:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child(int fd_in, int fd_out, int fd_other, t_pipex *cmd, char **envp)
{
	cmd->pid[cmd->index - 1] = fork();
	if (cmd->pid[cmd->index - 1] < 0)
		free_and_exit("fork", cmd);
	if (cmd->pid[cmd->index - 1] == 0)
	{
		if ((dup2(fd_in, 0) != -1) && (dup2(fd_out, 1) != -1))
		{
			if (cmd->index != cmd->last)
				close(fd_other);
			if (execve(cmd->path, cmd->name, envp))
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

int	here_doc(char *limiter, t_pipex *cmd, char **envp)
{
	char	*read_line;
	int		len_limiter;
	//char	file_name[7];
	int	fd;


	len_limiter = ft_strlen(limiter);
	read_line = NULL;
	/*fd = open("/dev/random", O_RDONLY);//proteger
	if (fd == -1)
		perror("open");
	if (read(fd, file_name, 7) == -1)
	{
		perror("read");
		
	}//close
	close(fd);
	*/
	fd = open("./tmp", O_WRONLY | O_CREAT, S_IWUSR);
	if (fd == -1)
		perror("open");
	read_line = get_next_line(0);
	ft_putstr_fd(read_line, fd);
	while (ft_strncmp(limiter, read_line, len_limiter) != 0)
	{
		read_line = get_next_line(0);
		ft_putstr_fd(read_line, fd);
		
	}
	free(read_line);
	close(fd);
	fd = open("./tmp", O_RDONLY);
	if (child(fd, cmd->fd[1], cmd->fd[0], cmd, envp) != 1)
		free_and_exit("command fail", cmd);
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
		if (check_command(av[i], envp, cmd) == 0)
			write(2, "command not found\n", 18);
		else if (cmd->index == cmd->first)
		{
			if (cmd->if_here_doc == 1)
			{
				if (here_doc(av[2], cmd, envp) != 1)
					free_and_exit("command fail", cmd);
			}
			else if (child(cmd->infile, cmd->fd[1], cmd->fd[0], cmd, envp) != 1)
				free_and_exit("command fail first cmd", cmd);
			
		}
		else if ((cmd->index == cmd->last) && (child(cmd->fd[0], cmd->outfile, cmd->fd[1], cmd, envp) != 1))
			free_and_exit("command fail last cmd", cmd);
		else if ((cmd->index != cmd->first) && (cmd->index != cmd->last))
		{
			cmd->previous_fd = cmd->fd[0];
			if (pipe(cmd->fd) == -1)
				free_and_exit("pipe", cmd);
			if (child(cmd->previous_fd, cmd->fd[1], cmd->fd[0], cmd, envp) == 0)
				free_and_exit("command fail middle cmd", cmd);
		}
		i++;
		cmd->index++;
		free_tab(cmd->name);
		free(cmd->path);
	}
}
