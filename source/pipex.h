/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:47:18 by malancar          #+#    #+#             */
/*   Updated: 2023/07/16 21:07:36 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "get_next_line.h"

typedef struct s_pipex {
	int		infile;
	int		outfile;
	int		here_doc;
	char	*path;
	char	**name;
	int		fd[2];
	int		previous_fd;
	pid_t	*pid;
	int		max;
	int		first;
	int		last;
	int		index_pid;
	int		if_here_doc;
	int		index;
	char	rand_name[7];
	int		fd_tmp;
	char	**envp;
	char	**argv;

}	t_pipex;

int		init_struct(t_pipex *cmd, int ac);
int		check_limiter(char *str, char *limiter);
int		ft_strcmp(char *s1, char *s2);
int		check_command(char *str, t_pipex *cmd);
int		check_access(t_pipex *cmd, char *path);
int		ft_strchr(char *str, char c);

char	**ft_split(char *str, char c);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2, char c);

void	error_cmd(int return_value, t_pipex *cmd);
void	first_cmd(t_pipex *cmd);
void	open_infile(t_pipex *cmd, char *first_arg);
void	exec_cmd(int fd_in, int fd_out, int fd_other, t_pipex *cmd);
void	here_doc(char *limiter, t_pipex *cmd);
void	open_outfile(t_pipex *cmd, char *last_arg);
void	open_and_fill_here_doc(t_pipex *cmd, char *limiter);
void	ft_putstr_fd(char *str, t_pipex *cmd);
void	free_tab(char **tab);
void	free_and_exit(char *str, t_pipex *cmd);
void	pipex(t_pipex *cmd);
void	fill_here_doc(char **read_line, char *limiter, t_pipex *cmd);

#endif