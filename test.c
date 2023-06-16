/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:24:28 by malancar          #+#    #+#             */
/*   Updated: 2023/06/16 16:38:40 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

int main(int ac, char **av)
{
	int	infile;
	int	outfile;
	int	pipe_fd[2];
	//int	parent;
	int	child;

	if (ac < 2)
		return (0);
	infile = open(av[1], O_RDONLY);
	if (infile == -1)
	{
		close(infile);
		return (0);
	}
	outfile = open(av[2], O_WRONLY);
	if (outfile == -1)
	{
		outfile = open(av[2], O_CREAT, S_IWUSR);
		if (outfile == 1)
		{
			close(outfile);
			return (0);
		}
	}
	int return_value;
	return_value = 0;
	return_value = pipe(pipe_fd);
	printf("pipe_fd = %d\n", pipe_fd[0]);
	printf("return value = %d\n", return_value);
	/*infile dup2 stdin // duplique le fd de stdin dans le fd de infile//duplique le fd de stdout dans le pipe 
	cmd1  read infile	/ execve in pipe_fd[0]
	//duplique stdin dans le pipe et dup stdout dans outfile
	cmd2 read from pipe_fd[1]
	execve in outfile 
	*/
	//printf("infile = %d\n", infile);
	//printf("outfile = %d\n", outfile);
	//close(infile);
	//close(outfile);

}
