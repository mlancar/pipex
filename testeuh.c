/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testeuh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:31:43 by malancar          #+#    #+#             */
/*   Updated: 2023/06/23 22:00:29 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	char	**cmd1;
	char	**cmd2;
	char	*valid_cmd_path;
	char	*valid_cmd_path2;
	int		child1;
	int		child2;
	int		infile;
	int		outfile;
	int		status;

	if (ac < 5)
		return (0);
	//printf("%d\n", ac - 3);
	//printf("ici : %p\n", &valid_cmd_path);
	//check_command(av[2], envp, &cmd, &valid_cmd_path);
	int		i;
	i = 0;
	cmd1 = ft_split(av[2], ' ');
	cmd2 = ft_split(av[3], ' ');
	if (!cmd1)
		return (0);
	if (!cmd2)
		return (0);
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
	if (check_access(cmd2[0], &envp[i][5], &valid_cmd_path2) == 0)
	{
		free_tab(cmd2);
		printf("error");
		return (1);
	}
	//fd = init_fd(av[1], av[3], infile, outfile);
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
		outfile = open(av[4], O_CREAT, S_IRWXU);

		if (outfile == 1)
		{
			close(outfile);
			return (0);
		}
	}
	//printf("infile = %d\n", infile);
	//printf("outfile = %d\n", outfile);
	pipe(fd);
	//printf("fd[0] = %d\n", fd[0]);
	//printf("fd[1] = %d\n", fd[1]);
	child1 = fork();
	if (child1 < 0)
	{
		printf("error child1\n");
		return (0);
	}
	if (child1 == 0)//child // cmd2
	{
		//printf("coucou child1\n");
		dup2(infile, 0);//read from infile not stdin
		dup2(fd[1], 1);//write in pipe exit not stdout
		close(fd[0]);// close entree pipe
		close(outfile);// close outfile bc write in pipe exit
		execve(valid_cmd_path, cmd1, envp);
		printf("execve marche pas :(\n");
		//free
		//exit
	}
	child2 = fork();
	if (child2 < 0)
	{
		printf("error child2\n");
		return (0);
	}
	else if (child2 == 0)
	{
		//printf("coucou child2\n");
		dup2(fd[0], 0);//read from pipe entree not stdin
		dup2(outfile, 1);//write in outfile not stdout
		close(infile);//close sortie pipe bc write in outfile
		close(fd[1]);//close infile bc read from pipe
		execve(valid_cmd_path2, cmd2, envp);
		//free
		//exit
		printf("execve marche pas :(\n");
	}
	else//parent
	{
		close(fd[0]);
		close(fd[1]);
		close(infile);
		close(outfile);
		waitpid(child1, &status, 0);
		waitpid(child2, &status, 0);
	}
}
