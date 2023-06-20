/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:47:18 by malancar          #+#    #+#             */
/*   Updated: 2023/06/20 16:29:37 by malancar         ###   ########.fr       */
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

typedef struct s_pipex {

}	t_pipex;

int	check_command(char av[2], char **envp, char ***cmd, char **valid_cmd_path);
int		check_access(char *cmd, char *path, char **cmd_path);
int		init_fd(char *infile, char *outfile, int fd[2]);
char	**ft_split(char *str, char c);
char	*ft_strjoin(char *s1, char *s2, char c);
void	free_tab(char **tab);

#endif