/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:51:40 by malancar          #+#    #+#             */
/*   Updated: 2023/07/09 18:40:22 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	cmd;
	int		i;
	int		status;
	
	if ((ft_strncmp("here_doc", av[1], 8) == 0) && (ac >= 6))
	{
		cmd.if_here_doc = 1;
		cmd.max = ac - 4;
		open_outfile(&cmd, av[ac - 1]);
	}
	else
	{
		if (ac < 5)
			return (0);
		open_infile(&cmd, av[1]);
		open_outfile(&cmd, av[ac - 1]);
		cmd.if_here_doc = 0;
		cmd.max = ac - 3;//init cmd start
	}

	cmd.index = 1;
	cmd.first = 1;
	cmd.last = cmd.max;
	i = 0;
	cmd.pid = malloc(sizeof(pid_t) * cmd.max);
	if (!cmd.pid)
		return (printf("pid error"), 0);//init cmd end
	pipex(&cmd, av, envp);
	while (i > 0)
	{	
		waitpid(cmd.pid[i], &status, 0);
		i--;
	}
	free(cmd.pid);
}
