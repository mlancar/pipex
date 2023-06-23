/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/06/23 22:07:31 by malancar         ###   ########.fr       */
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


int	child_process(pipe_t )
{
	dup2(infile, 0);//read from infile not stdin
	dup2(fd1[1], 1);//write in pipe exit not stdout
	close(fd1[0]);// close entree pipe
	close(outfile);// close outfile bc write in pipe exit
	execve(valid_cmd_path, cmd1, envp);
	printf("execve marche pas :(\n");
	//free
	//exit
}

/*int	parent_process()
{
	
}

void	pipex()
{
	
}*/

int	main(int ac, char **av, char **envp)
{
	int		fd1[2];
	int		fd2[2];
	char	**cmd1;
	char	*valid_cmd_path;
	char	*valid_cmd_path2;
	int		child1;
	int		child2;
	int		infile;
	int		outfile;
	int		status;
	int		nbr_args;

	if (ac < 5)
		return (0);
	//printf("ici : %p\n", &valid_cmd_path);
	//check_command(av[2], envp, &cmd1, &valid_cmd_path);
	//check_command(av[3], envp, &cmd2, &valid_cmd_path2);
	//fd = init_fd(av[1], av[3], fd[2]);
	nbr_args = ac - 3;
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
	pipe1(fd1);
	pipe2(fd2);
	//printf("fd[0] = %d\n", fd[0]);
	//printf("fd[1] = %d\n", fd[1]);
	while (nbr_args > 0)
	{
		child = fork();
		if (child1 < 0)
		{
			printf("error child1\n");
			return (0);
		}
		if (child == 0)
		{
			if (check_command(av[2], envp, &cmd1, &valid_cmd_path) == 0)
			{
				printf("error");
				return (0);
			}
			child_process();
		}
		else//parent
		{
			
		}
		nbr_args--;
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
		printf("execve marche pas :(\n");
	}
	//printf("coucouc ici\n");
	close(fd1[0]);
	close(fd1[1]);
	close(infile);
	close(outfile);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);

}
