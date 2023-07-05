/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:47:18 by malancar          #+#    #+#             */
/*   Updated: 2023/07/05 15:01:55 by malancar         ###   ########.fr       */
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

typedef struct s_pipex {
    int     infile;
    int     outfile;
    char    *path;
    char    **name;
   // int     child;
    int     fd[2];
    int     previous_fd;
    pid_t     *pid;
    int     max;
    int     first;
    int     last;
    int     index;
}	t_pipex;

void    free_everything(t_pipex *cmd);
void	free_tab(char **tab);
void	error_cmd(t_pipex *cmd);
void    free_and_exit(char *str, t_pipex *cmd);
void	ft_putstr_fd(char *str, int fd);
int     check_command(char *str, char **envp, t_pipex *cmd);
int		check_access(t_pipex *cmd, char *path);
int		init_fd(char *infile, char *outfile);
char	**ft_split(char *str, char c);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2, char c);
void	free_tab(char **tab);
void	pipex(t_pipex *cmd, char **av, char **envp);
int     middle_cmd(t_pipex *cmd, char **envp);
int     last_cmd(t_pipex *cmd, char **envp);
int     open_infile(t_pipex *cmd, char *first_arg);
int     open_outfile(t_pipex *cmd, char *last_arg);

#endif