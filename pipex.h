/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:47:18 by malancar          #+#    #+#             */
/*   Updated: 2023/06/27 16:09:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
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

typedef struct s_pipex {
    int     infile;
    int     outfile;
    char    *path;
    char    **name;
   // int     child;
    int     fd[2];
    int     previous_fd;
    int     *pid;
    int     nbr;
    int     first;
    int     last;
    int     index;
}	t_pipex;


int     check_command(char *str, char **envp, t_pipex *cmd);
int		check_access(t_pipex *cmd, char *path);
int		init_fd(char *infile, char *outfile);
char	**ft_split(char *str, char c);
char	*ft_strjoin(char *s1, char *s2, char c);
void	free_tab(char **tab);
int     pipex(char *first_arg, char *last_arg, t_pipex *cmd,char **envp);
int     first_cmd(t_pipex *cmd, char **envp);
int     middle_cmd(t_pipex *cmd, char **envp);
int     last_cmd(t_pipex *cmd, char **envp);
int     open_infile(t_pipex *cmd, char *first_arg);
int     open_outfile(t_pipex *cmd, char *last_arg);

#endif