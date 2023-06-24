/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/06/25 00:48:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*void	close_fd()
{
	close(infile);
	close(outfile);
	//printf("fd = %d\n", infile);
}*/

void	ft_error()
{
	printf("error");
	return (0);
}

void	child_process1(t_pipex pipex, char **envp)
{
	
	if (first_arg)
	{
		dup2(pipex.fd1[1], 1);//write in pipe exit not stdout
		dup2(pipex.infile, 0);//read from infile not stdin
		close(pipex.fd1[0]);// close entree pipe
		close(pipex.outfile);// close outfile bc write in pipe exit
	}
	dup2(pipex.fd1[0]);
	close(pipex.fd1[1]);
	else if (last arg)
	{
		dup2(pipex.outfile);
		close(pipex.fd2[1]);
	}
	else
	{
		dup2(pipex.fd2[1]);//write in pipe2 exit
		close(pipex.fd2[0]);
	}
	execve(pipex.valid_cmd_path, pipex.cmd1, envp);
	printf("execve marche pas :(\n");
	//free
	exit ;
}

void	child_process2(t_pipex pipex)
{
	dup2(pipex.fd1[0]);//read from first pipe entree
	close(pipex.fd1[1]);
	if(last arg)
	{
		dup2(pipex.outfile);//write in pipe2 exit
		close(pipex.fd2[1]);
	}
	else
	{
		dup2(pipex.fd2[1]);//write in pipe2 exit
		close(pipex.fd2[0]);
	}
	execve(pipex.valid_cmd_path, pipex.cmd1, envp);
	printf("execve marche pas :(\n");
	//free
	exit ;
}



void	fork1(t_pipex pipex)
{
	pipex.child1 = fork();
	if (pipex.child1 < 0)
		ft_error();
	if (child == 0)
	{
		if (check_command(av[2], envp, &cmd1, &valid_cmd_path) == 0)
			ft_error();
		child_process1(&pipex);
	}
}

void	fork2(t_pipex pipex)
{
	child2 = fork();
	if (child2 < 0)
		ft_error();
	else if (pipex.child2 == 0)
	{
		if (check_command(av[2], envp, &cmd1, &valid_cmd_path) == 0)
			ft_error();
		child_process2(&pipex);
	}
}

int	parent_process()
{
	close(pipex.fd1[0]);
	close(pipex.fd1[1]);
	close(pipex.infile);
	close(pipex.outfile);
	waitpid(pipex.child1, &status, 0);
	waitpid(pipex.child2, &status, 0);
}
void	pipexe(t_pipex pipex)
{
	int	pipe1;
	int	pipe2;
	int		nbr_args;
	
	nbr_args = ac - 3;
	pipe1(pipex.fd1);//if arg > 1
	pipe2(pipex.fd2);// if arg > 2
	while (nbr_args > 0)
	{
		if ((cmd1==av[2]) % 2 == 0)//paire//first cmd always paire
			fork1(&pipex);
		else if(cmd_nbr % 2 == 1)//impaire
			fork2(&pipex);
		else//parent	
			parent_process(&pipex);//printf("coucouc ici\n");
		nbr_args--;
	}
}

void	open_files(t_pipex pipex, char *first_arg, char *last_arg)
{
	piex.infile = open(first_arg, O_RDONLY);
	if (pipex.infile == -1)
	{
		close(pipex.infile);
		return (0);
	}
	pipex.outfile = open(last_arg, O_WRONLY);
	if (pipex.outfile == -1)
	{
		//piepx.outfile = open(av[3], O_CREAT, S_IWUSR);
		pipex.outfile = open(last_arg, O_CREAT, S_IRWXU);

		if (pipex.outfile == 1)
		{
			close(pipex.outfile);
			return (0);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	pipex;
	int		status;

	if (ac < 5)
		return (0);
	open_files(&pipex, av[1], av[ac -1]);
	pipexe(&pipex);
	
}
