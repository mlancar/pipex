/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:28:37 by malancar          #+#    #+#             */
/*   Updated: 2023/06/20 17:56:47 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*int	check_command(char av[2], char **envp, char ***cmd, char **valid_cmd_path)
{
	int		i;

	printf("&cmd : %p\n", cmd);
	//printf("ici : %p\n", valid_cmd_path);
	i = 0;
	*cmd = ft_split(&av[2], ' ');
	if (!*cmd)
		return (1);
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	printf("&cmd la: %p\n", cmd);
	if (check_access(, &envp[i][5], valid_cmd_path) == 0)
	{
		free_tab(*cmd);
		printf("error ici\n");
		return (1);
	}
	return (1);
}
*/
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
