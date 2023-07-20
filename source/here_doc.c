/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:53:52 by malancar          #+#    #+#             */
/*   Updated: 2023/07/20 15:07:32 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_limiter(char *str, char *limiter)
{
	int	i;

	i = 0;
	if (!str || !limiter)
		return (0);
	while ((str[i] && limiter[i]))
	{
		if (str[i] != limiter[i])
			return (-1);
		i++;
	}
	if (str[i] == '\n' && limiter[i] == '\0')
		return (0);
	return (str[i] - limiter[i]);
}

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

	nbr_pipe = cmd->max - 1;
	while (nbr_pipe > 0)
	{
		write(1, "pipe ", 5);
		nbr_pipe--;
	}
	write(1, "here_doc> ", 10);
	*read_line = get_next_line(0, 0);
	if (*read_line == NULL)
		write(2, "\nwarning: here-doc delimited by end-of-file\n", 45);
	if (is_limiter(*read_line, limiter) != 0)
		ft_putstr_fd(*read_line, cmd->fd_tmp);
}

void	open_and_fill_here_doc(t_pipex *cmd, char *limiter)
{
	char	*read_line;

	get_rand_name(cmd);
	fill_here_doc(&read_line, limiter, cmd);
	while (is_limiter(read_line, limiter) != 0)
	{
		free(read_line);
		fill_here_doc(&read_line, limiter, cmd);
	}
	get_next_line(0, 1);
	free(read_line);
	close(cmd->fd_tmp);
}

void	here_doc(char *limiter, t_pipex *cmd)
{
	cmd->fd_tmp = 0;
	open_and_fill_here_doc(cmd, limiter);
	cmd->fd_tmp = open(cmd->rand_name, O_RDONLY);
	if (cmd->fd_tmp == -1)
		free_and_exit("open", cmd);
}
