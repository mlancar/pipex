/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:29:36 by malancar          #+#    #+#             */
/*   Updated: 2023/06/20 15:22:14 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_fd(char *infile, char *outfile, int fd[2])
{
	fd[0] = open(infile, O_RDONLY);
	if (fd[0] == -1)
	{
		close(fd[0]);
		return (0);
	}
	fd[1] = open(outfile, O_WRONLY);
	if (fd[1] == -1)
	{
		fd[1] = open(outfile, O_CREAT, S_IWUSR);
		if (fd[1] == 1)
		{
			close(fd[1]);
			return (0);
		}
	}
	return (1);
}
