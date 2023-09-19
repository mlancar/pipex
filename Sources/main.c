/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:51:40 by malancar          #+#    #+#             */
/*   Updated: 2023/07/19 18:53:43 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

int	init_struct(t_pipex *cmd, int ac)
{
	if ((ft_strcmp("here_doc", cmd->argv[1]) == 0) && (ac > 5))
	{
		cmd->if_here_doc = 1;
		cmd->index = 3;
		cmd->max = ac - 4;
		open_outfile(cmd, cmd->argv[ac - 1]);
	}
	else if ((ft_strcmp("here_doc", cmd->argv[1]) != 0) && (ac > 4))
	{
		cmd->if_here_doc = 0;
		open_infile(cmd, cmd->argv[1]);
		open_outfile(cmd, cmd->argv[ac - 1]);
		cmd->index = 2;
		cmd->max = ac - 3;
	}
	else
		return (0);
	cmd->index_pid = 1;
	cmd->first = 1;
	cmd->path = NULL;
	cmd->name = NULL;
	cmd->last = cmd->max;
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	cmd;
	int		status;

	cmd.envp = envp;
	cmd.argv = av;
	if (init_struct(&cmd, ac) == 0)
		return (0);
	cmd.pid = malloc(sizeof(pid_t) * cmd.max);
	if (!cmd.pid)
		return (write(1, "pid error\n", 10), 0);
	pipex(&cmd);
	cmd.index_pid--;
	while (cmd.index_pid > 0)
	{
		waitpid(cmd.pid[cmd.index_pid - 1], &status, 0);
		cmd.index_pid--;
	}
	free(cmd.pid);
}
