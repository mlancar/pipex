/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:24:28 by malancar          #+#    #+#             */
/*   Updated: 2023/06/13 20:07:11 by malancar         ###   ########.fr       */
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
	printf("infile = %d\n", infile);
	printf("outfile = %d\n", outfile);
	close(infile);
	close(outfile);

}
