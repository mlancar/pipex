/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:51:40 by malancar          #+#    #+#             */
/*   Updated: 2023/07/13 17:12:14 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_struct(t_pipex *cmd, char **av, int ac)
{
	if ((ft_strcmp("here_doc", av[1]) == 0) && (ac > 5))
	{
		cmd->if_here_doc = 1;
		cmd->index = 3;
		cmd->max = ac - 4;
		open_outfile(cmd, av[ac - 1]);
	}
	else if ((ft_strcmp("here_doc", av[1]) != 0) && (ac > 4))
	{
		cmd->if_here_doc = 0;
		open_infile(cmd, av[1]);
		open_outfile(cmd, av[ac - 1]);
		cmd->index = 2;
		cmd->max = ac - 3;
	}
	else
		return (0);
	cmd->index_pid = 1;
	cmd->first = 1;
	cmd->last = cmd->max;
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	cmd;
	int		i;
	int		status;

	i = 0;
	cmd.envp = envp;
	if (init_struct(&cmd, av, ac) == 0)
		return (0);
	cmd.pid = malloc(sizeof(pid_t) * cmd.max);
	if (!cmd.pid)
		return (printf("pid error"), 0);
	pipex(&cmd, av);
	while (i > 0)
	{	
		waitpid(cmd.pid[i], &status, 0);
		i--;
	}
	free(cmd.pid);
}
