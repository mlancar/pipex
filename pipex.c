/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/06/21 18:36:55 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


/*int	fork_process(int *parent_pid)
{
	*parent_pid = fork();
	if (*parent_pid == 0)//we are in the child process
		child_process(fd[0], cmd)
	else if (*parent_pid < 0)
	{
		printf("error\n");
		return (-1);
	}
}*/

/*void	close_fd()
{
	close(infile);
	close(outfile);
	//printf("fd = %d\n", infile);
}*/

/*
int	child_process()
{
	
}

int	parent_process()
{
	
}

void	pipex()
{
	
}*/

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	char	**cmd1;
	char	**cmd2;
	char	*valid_cmd_path;
	int		pid;
	int		infile;
	int		outfile;

	if (ac < 5)
		return (0);
	//printf("ici : %p\n", &valid_cmd_path);
	//heck_command(av[2], envp, &cmd, &valid_cmd_path);
	
	int		i;
	i = 0;
	cmd1 = ft_split(av[2], ' ');
	cmd2 = ft_split(av[3], ' ');
	if (!cmd1)
		return (1);
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	if (check_access(cmd1[0], &envp[i][5], &valid_cmd_path) == 0)
	{
		free_tab(cmd1);
		printf("error");
		return (1);
	}
	if (check_access(cmd2[0], &envp[i][5], &valid_cmd_path) == 0)
	{
		free_tab(cmd2);
		printf("error");
		return (1);
	}
	//fd = init_fd(av[1], av[3], fd[2]);
	//infile = 
	infile = open(av[1], O_RDONLY);
	if (infile == -1)
	{
		close(infile);
		return (0);
	}
	outfile = open(av[4], O_WRONLY);
	if (outfile == -1)
	{
		//fd[1] = open(av[3], O_CREAT, S_IWUSR);
		outfile= open(av[4], O_CREAT, S_IRWXU);

		if (outfile == 1)
		{
			close(outfile);
			return (0);
		}
	}
	//printf("fd[0] = %d\n", fd[0]);
	//printf("fd[1] = %d\n", fd[1]);
	//infile = fd[0];
	//outfile = fd[1];
	pipe(fd);
	pid = fork();
	if (pid < 0)
	{
		printf("error\n");
		return (0);
	}
	if (pid == 0)//child
	{
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(infile);
		execve(valid_cmd_path, cmd1, envp);
		printf("ca marche pas :(\n");
	}
	else//parent
	{
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		close(fd[1]);
		close(outfile);
		execve(valid_cmd_path, cmd2, envp);
		printf("ca marche pas :(\n");
	}
	//si execve reussi, ne revient pas ici, sinon il faut free

}
