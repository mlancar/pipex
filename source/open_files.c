/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:13:28 by malancar          #+#    #+#             */
/*   Updated: 2023/07/12 20:36:49 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_struct(t_pipex *cmd, char **av, int ac)
{

	if ((ft_strcmp("here_doc", av[1]) == 0) && (ac >= 6))
	{
		cmd->if_here_doc = 1;
		cmd->index = 3;
		cmd->max = ac - 4;
		open_outfile(cmd, av[ac - 1]);
	}
	else
	{
		if (ac < 5)
			return (0);
		open_infile(cmd, av[1]);
		open_outfile(cmd, av[ac - 1]);
		cmd->if_here_doc = 0;
		cmd->index = 2;
		cmd->max = ac - 3;//init cmd start
	}
	cmd->index_pid = 1;
	cmd->first = 1;
	cmd->last = cmd->max;
	return (1);
}

/*int	get_rand_name(int fd, t_pipex *cmd)
{
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		perror("open");
	if (read(fd, cmd->rand_name, 7) == -1)
		perror("read");
	close(fd);
	// fd = open(cmd->rand_name,  O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP 
	// 	| S_IROTH);
}
*/

void	fill_here_doc(char **read_line, char *limiter, t_pipex *cmd)
{
	write(0, "pipe here_doc> ", 15);
	*read_line = get_next_line(0, 0);
	if (*read_line == NULL)
		write(2, "warning: here-doc at line 1 delimited by end-of-file\n", 54);
	if (check_limiter(*read_line, limiter) != 0)
		ft_putstr_fd(*read_line, cmd);
}


int	open_and_fill_here_doc(t_pipex *cmd, char *limiter)
{
	char	*read_line;
		
	cmd->fd_tmp = open("./tmp",  O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP 
		| S_IROTH);
	if (cmd->fd_tmp == -1)
		free_and_exit("open", cmd);
	fill_here_doc(&read_line, limiter, cmd);	
	while (check_limiter(read_line, limiter) != 0)
	{
		free(read_line);
		fill_here_doc(&read_line, limiter, cmd);	
	}
	get_next_line(0, 1);
	free(read_line);
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
	cmd->outfile = open(last_arg, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
	if (cmd->outfile == -1)
	{
		perror("open");
		
	}
	return (1);
}