/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:28:37 by malancar          #+#    #+#             */
/*   Updated: 2023/07/12 20:48:08 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_limiter(char *str, char *limiter)
{
	int	i;

	i = 0;
	if (!str || !limiter)
		return (0);
	while ((str[i] && limiter[i]))
	{
		if (str[i] != limiter[i])
			return (-1);
		i++;
	}
	if (str[i] == '\n' && limiter[i] == '\0')
		return (0);
	return (str[i] - limiter[i]);
}

int	check_command(char *str, t_pipex *cmd)
{
	int		i;

	i = 0;
	cmd->name = ft_split(str, ' ');
	if (!cmd->name)
		return (1);
	while (cmd->envp[i])
	{
		if (strncmp(cmd->envp[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	if (check_access(cmd, &cmd->envp[i][5]) == 0)
		return (0);
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
		{
			free_tab(split_path);
			return (1);
		}
		free(cmd->path);
		
		i++;
	}
	free_tab(split_path);
	cmd->path = ft_strdup(*(cmd->name));
	if (access(cmd->path, F_OK) == 0)
		return (1);
	return (0);
}
