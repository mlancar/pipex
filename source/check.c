/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:28:37 by malancar          #+#    #+#             */
/*   Updated: 2023/07/19 18:52:17 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

int	have_slash(t_pipex *cmd)
{
	if (ft_strchr(cmd->name[0], '/'))
	{
		cmd->path = ft_strdup(*(cmd->name));
		if (access(cmd->path, X_OK) == 0)
			return (1);
	}
	return (0);
}

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
	int		find_path;
	char	*path;

	i = 0;
	find_path = 0;
	if (cmd->argv[cmd->index][0] == '\0')
		error_empty_string(cmd);
	cmd->name = ft_split(str, ' ');
	if (!cmd->name || (!cmd->name[0]))
		return (0);
	while (cmd->envp[i])
	{
		if (cmd->envp[i][0] == 'P' && cmd->envp[i][1] == 'A' &&
			cmd->envp[i][2] == 'T' && cmd->envp[i][3] == 'H' &&
			cmd->envp[i][4] == '=')
			find_path = i;
		i++;
	}
	path = &cmd->envp[find_path][5];
	if (find_path == 0)
		path = NULL;
	if (check_access(cmd, path) == 0)
		return (0);
	return (1);
}

int	check_access(t_pipex *cmd, char *path)
{
	char	**split_path;
	int		i;

	i = 0;
	if (have_slash(cmd))
		return (0);
	split_path = ft_split(path, ':');
	while (split_path && split_path[i])
	{
		cmd->path = ft_strjoin(split_path[i], *(cmd->name), '/');
		if (access(cmd->path, X_OK) == 0)
		{
			free_tab(split_path);
			return (1);
		}
		free(cmd->path);
		i++;
	}
	if (split_path)
		free_tab(split_path);
	cmd->path = ft_strdup(*(cmd->name));
	if (access(cmd->path, X_OK) == 0)
		return (1);
	return (0);
}
