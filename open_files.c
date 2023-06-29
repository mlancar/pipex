/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:13:28 by malancar          #+#    #+#             */
/*   Updated: 2023/06/29 13:24:53 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(t_pipex *cmd, char *first_arg)
{
	//if on peut pas lire depuis infile
	// la premiere cmd s'execute pas 
	//mais le reste oui
	//dprintf(2, "first_arg = %s\n", first_arg);
	cmd->infile = open(first_arg, O_RDONLY);
	if (cmd->infile == -1)
	{
		//perror("infile does not exist\n");
		perror(NULL);
		strerror();
		//write(2, "infile doest not exist\n", 23);
	}
	//dprintf(2, "infile = %d\n", cmd->infile);
	/*if (cmd->infile == -1)
	{
		dprintf(2, "coucou infile\n");
		return (0);
	}*/
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