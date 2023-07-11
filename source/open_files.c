/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:13:28 by malancar          #+#    #+#             */
/*   Updated: 2023/07/11 17:46:33 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_tmp_file(int fd)
{
	/*fd = open("/dev/random", O_RDONLY);//proteger
	if (fd == -1)
		perror("open");
	if (read(fd, file_name, 7) == -1)
	{
		perror("read");
		
	}//close
	close(fd);
	*/
	fd = open("./tmp", O_WRONLY | O_CREAT, S_IRWXU);
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