/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 21:28:45 by malancar          #+#    #+#             */
/*   Updated: 2023/07/18 16:36:32 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_and_exit(char *str, t_pipex *cmd)
{
	free_tab(cmd->name);
	free(cmd->path);
	free(cmd->pid);
	perror(str);
	exit(EXIT_FAILURE);
}

void	error_cmd(int return_value, t_pipex *cmd)
{
	free_tab(cmd->name);
	free(cmd->path);
	free(cmd->pid);
	check_close(cmd->fd[0]);
	check_close(cmd->fd[1]);
	check_close(cmd->outfile);
	if (cmd->if_here_doc == 0)
		check_close(cmd->infile);
	else
		check_close(cmd->fd_tmp);
	if ((cmd->index_pid != cmd->first) && (cmd->index_pid != cmd->last))
		check_close(cmd->previous_fd);
	exit(return_value);
}


