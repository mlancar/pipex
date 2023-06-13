/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/06/13 19:23:54 by malancar         ###   ########.fr       */
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

/*void	pipex(int f1, int f2)
{
	int end[2];

	pipe(end);
}*/

/*void	exec_cmd1(int fd, char *valid_cmd_path)
{
	
	execve(const char *fichier, char *const argv[], char *const envp[]);
}*/

int	main(int ac, char **av, char **envp)
{
	int		i;
	char	**cmd;
	char	*valid_cmd_path;

	if (ac < 2)
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
	int infile = open(av[1], O_CREAT);
	int outfile = open(av[3], O_CREAT);
	//int infile = open(av[1], O_RDONLY);
	//int outfile = open(av[1], O_RDONLY);
	printf("outfile = %d\n", infile);
	printf("infile = %d\n", outfile);
	close(infile);
	close(outfile);
	//printf("fd = %d\n", infile);
	execve(valid_cmd_path, cmd, envp);
	//si execve reussi ne revient pas ici, sinon il faut free

}

