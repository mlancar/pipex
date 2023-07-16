/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:13:28 by malancar          #+#    #+#             */
/*   Updated: 2023/07/16 20:23:23 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_rand_name(t_pipex *cmd)
{
	int	i;

	i = 0;
	cmd->fd_tmp = open("/dev/random", O_RDONLY);
	if (cmd->fd_tmp == -1)
		free_and_exit("open", cmd);
	if (read(cmd->fd_tmp, cmd->rand_name, 6) == -1)
		free_and_exit("open", cmd);
	cmd->rand_name[6] = '\0';
	i = 0;
	while (i < 6)
	{
		cmd->rand_name[i] = cmd->rand_name[i] % 26;
		if (cmd->rand_name[i] < 0)
			cmd->rand_name[i] = cmd->rand_name[i] + 26;
		cmd->rand_name[i] = cmd->rand_name[i] + 97;
		i++;
	}
	close(cmd->fd_tmp);
	cmd->fd_tmp = open(cmd->rand_name, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR
			| S_IWUSR | S_IRGRP);
	if (cmd->fd_tmp == -1)
		free_and_exit("open", cmd);
}

void	fill_here_doc(char **read_line, char *limiter, t_pipex *cmd)
{
	int	nbr_pipe;

	nbr_pipe = cmd->max;
	while (nbr_pipe > 0)
	{
		write(1, "pipe ", 5);
		nbr_pipe--;
	}
	write(1, "here_doc> ", 10);
	*read_line = get_next_line(0, 0);
	if (*read_line == NULL)
		write(2, "\nwarning: here-doc delimited by end-of-file\n", 45);
	if (check_limiter(*read_line, limiter) != 0)
		ft_putstr_fd(*read_line, cmd);
}

void	open_and_fill_here_doc(t_pipex *cmd, char *limiter)
{
	char	*read_line;

	get_rand_name(cmd);
	fill_here_doc(&read_line, limiter, cmd);
	while (check_limiter(read_line, limiter) != 0)
	{
		free(read_line);
		fill_here_doc(&read_line, limiter, cmd);
	}
	get_next_line(0, 1);
	free(read_line);
	close(cmd->fd_tmp);
}

void	open_infile(t_pipex *cmd, char *first_arg)
{
	cmd->infile = open(first_arg, O_RDONLY);
	if (cmd->infile == -1)
		perror("open");
}

void	open_outfile(t_pipex *cmd, char *last_arg)
{
	if (cmd->if_here_doc == 1)
	{
		cmd->outfile = open(last_arg, O_RDWR | O_APPEND | O_CREAT, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IROTH);
		if (cmd->outfile == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		cmd->outfile = open(last_arg, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IROTH);
		if (cmd->outfile == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
	}
}
