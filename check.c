/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:28:37 by malancar          #+#    #+#             */
/*   Updated: 2023/06/23 21:09:32 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_command(char *str, char **envp, char ***cmd, char **valid_cmd_path)
{
	int		i;

	//printf("&cmd : %p\n", cmd);
	//printf("ici : %p\n", valid_cmd_path);
	i = 0;
	*cmd = ft_split(str, ' ');
	if (!*cmd)
		return (1);
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	//printf("&cmd la: %p\n", cmd);
	//printf("commande: %s\n", cmd[0][0]);
	if (check_access((*cmd)[0], &envp[i][5], valid_cmd_path) == 0)
	{
		free_tab(*cmd);
		printf("error check_command\n");
		return (0);
	}
	return (1);
}

int	check_access(char *cmd, char *path, char **cmd_path)
{
	char	**split_path;
	int		i;

	//printf("ici : %p\n", cmd_path);
	//printf("&cmd ici: %p\n", cmd);
	i = 0;
	split_path = ft_split(path, ':');
	if (!split_path)
		return (0);
	while (split_path[i])
	{
		*cmd_path = ft_strjoin(split_path[i], cmd, '/');
		//printf("cmd_path = %s\n", *cmd_path);
		if (access(*cmd_path, F_OK) == 0)
			return (1);
		free(*cmd_path);
		i++;
	}
	*cmd_path = strdup(cmd);
	if (access(*cmd_path, F_OK) == 0)
		return (1);
	//printf("check_access: %s\n", *cmd_path);
	return (0);
}
