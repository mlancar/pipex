/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:13:28 by malancar          #+#    #+#             */
/*   Updated: 2023/07/07 14:16:44 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc(t_pipex *cmd, )
{
	t_pipex	here_doc;
	int		read_line;

	if (pipe(cmd->fd) == 0)
		free_and_exit("pipe", cmd);
	here_doc.pid= fork();
	if (here_doc.pid < 0)
		free_and_exit("fork", cmd);
	else if (here_doc.pid == 0)
	{
		read_line = get_next_line(0);
		
	}
	else
	{
		
	}
	
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