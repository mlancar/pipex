/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:28:37 by malancar          #+#    #+#             */
/*   Updated: 2023/06/30 18:12:26 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_command(char *str, char **envp, t_pipex *cmd)
{
	int		i;

	i = 0;
	cmd->name = ft_split(str, ' ');
	if (!cmd->name)
		return (1);
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	if (check_access(cmd, &envp[i][5]) == 0)
	{
		free_tab(cmd->name);
		return (0);
	}
	return (1);
}

int	check_access(t_pipex *cmd, char *path)
{
	char	**split_path;
	int		i;

	i = 0;
	split_path = ft_split(path, ':');
	if (!split_path)
		return (0);
	while (split_path[i])
	{
		cmd->path = ft_strjoin(split_path[i], *(cmd->name), '/');
		if (access(cmd->path, F_OK) == 0)
			return (1);
		free(cmd->path);
		i++;
	}
	cmd->path = strdup(*(cmd->name));//ft_strdup
	if (access(cmd->path, F_OK) == 0)
		return (1);
	return (0);
}
