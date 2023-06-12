/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:47:18 by malancar          #+#    #+#             */
/*   Updated: 2023/06/12 20:20:56 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
//a utiliser pour l'index du pipe :
# define WRITE 1
# define READ 0

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

int		check_access(char *cmd, char *path);
int		check_access(char *cmd, char *path, char **cmd_path);
char	**ft_split(char *str, char c);
char	*ft_strjoin(char *s1, char *s2, char c);
void	free_tab(char **tab);

#endif