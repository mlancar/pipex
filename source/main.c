/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:51:40 by malancar          #+#    #+#             */
/*   Updated: 2023/07/12 20:50:05 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		return (printf("pid error"), 0);//init cmd end
	pipex(&cmd, av);
	while (i > 0)
	{	
		waitpid(cmd.pid[i], &status, 0);
		i--;
	}
	free(cmd.pid);
}
