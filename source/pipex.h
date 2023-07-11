/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:47:18 by malancar          #+#    #+#             */
/*   Updated: 2023/07/11 19:07:59 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define ERROR_CMD "command not found\n"
# define ERROR_OPEN "No such file\n"
//a utiliser pour l'index du pipe :

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
# include "get_next_line/get_next_line.h"

typedef struct s_pipex {
    int     infile;
    int     outfile;
    int     here_doc;
    char    *path;
    char    **name;
    int     fd[2];
    int     previous_fd;
    pid_t     *pid;
    int     max;
    int     first;
    int     last;
    int     index;
    int     if_here_doc;

}	t_pipex;

int     open_tmp_file(int fd);
int     check_limiter(char *str, char *limiter);
int     open_here_doc(t_pipex *cmd, char *first_arg);
int     here_doc(char *limiter, t_pipex *cmd, char **envp);
int		ft_strcmp(char *s1, char *s2);
int     check_command(char *str, char **envp, t_pipex *cmd);
int		check_access(t_pipex *cmd, char *path);
int     check_here_doc(char *str, int ac);
int     middle_cmd(t_pipex *cmd, char **envp);
int     last_cmd(t_pipex *cmd, char **envp);
int     open_infile(t_pipex *cmd, char *first_arg);
int     open_outfile(t_pipex *cmd, char *last_arg);

char	**ft_split(char *str, char c);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2, char c);

void	ft_putstr_fd(char *str, int fd);
void	free_tab(char **tab);
void    free_and_exit(char *str, t_pipex *cmd);
void	pipex(t_pipex *cmd, char **av, char **envp);

#endif