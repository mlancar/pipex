/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:31:21 by malancar          #+#    #+#             */
/*   Updated: 2023/07/12 17:50:32 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H 
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd, int mode);
char	*join(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
char	*dup_line(char **s);
char	*ft_memmove(char *dest, char *src, int n);
char	*ft_checkn(char **save, int n);
void	ft_check(char **save, char *buf);
void	ft_check_read(char *buf, int r);
int		ft_strlen(char *str);
int		ft_strchr(char *str, char c);
#endif
