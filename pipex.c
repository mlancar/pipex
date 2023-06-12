/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/06/12 20:18:29 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_access(char *cmd, char *path, char **cmd_path)
{
	char	**split_path;
	int		i;

	i = 0;
	split_path = ft_split(path, ':');
	if (!split_path)
		return (0);
	while (split_path[i])
	{
		*cmd_path = ft_strjoin(split_path[i], cmd, '/');
		printf("cmd_path = %s\n", *cmd_path);
		if (access(*cmd_path, F_OK) == 0)
			return (1);
		free(*cmd_path);
		i++;
	}
	*cmd_path = strdup(cmd);
	if (access(*cmd_path, F_OK) == 0)
		return (1);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	char	**cmd;
	char	*cmd_path_valid;

	if (ac < 2)
		return (0);
	i = 0;
	cmd = ft_split(av[1], ' ');
	if (!cmd)
		return (1);
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	if (check_access(cmd[0], &envp[i][5], &cmd_path_valid) == 0)
	{
		free_tab(cmd);
		printf("error");
		return (1);//127 command not found
	}
	execve(cmd_path_valid, cmd, envp);
	//si execve reussi ne revient pas ici, sinon il faut free

}

