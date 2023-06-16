/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/06/16 18:00:26 by malancar         ###   ########.fr       */
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
		//printf("cmd_path = %s\n", *cmd_path);
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

int	init_fd(char *infile, char *outfile, int fd[2])
{
	fd[0] = open(infile, O_RDONLY);
	if (fd[0] == -1)
	{
		close(fd[0]);
		return (0);
	}
	fd[1] = open(outfile, O_WRONLY);
	if (fd[1] == -1)
	{
		fd[1] = open(outfile, O_CREAT, S_IWUSR);
		if (fd[1] == 1)
		{
			close(fd[1]);
			return (0);
		}
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	char	**cmd;
	char	*valid_cmd_path;
	int		fd[2];

	if (ac < 4)
		return (0);
	i = 0;
	cmd = ft_split(av[2], ' ');
	if (!cmd)
		return (1);
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	if (check_access(cmd[0], &envp[i][5], &valid_cmd_path) == 0)
	{
		free_tab(cmd);
		printf("error");
		return (1);//127 command not found
	}
	init_fd(av[1], av[3], &fd[2]);
	dup2(0, fd[0]);
	dup2(1, fd[1]);
	pid = fork()
	if (pid > 0)
		child
	else if (pid == -1)
		error
	else if
		
	//dup2(1, pipe_fd[0])
	//close(infile);
	//close(outfile);
	//printf("fd = %d\n", infile);
	execve(valid_cmd_path, cmd, envp);
	//si execve reussi ne revient pas ici, sinon il faut free

}
