/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 12:51:40 by malancar          #+#    #+#             */
/*   Updated: 2023/07/16 21:13:33 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_memmove(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	if (dest > src)
	{
		i = n;
		while (i > 0)
		{
			dest[i - 1] = src [i - 1];
			i--;
		}
		return (dest);
	}
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

void	check_save(char **save, char *buf)
{
	if (*save)
			*save = join(*save, buf);
	if (!*save)
		*save = buf;
}

char	*check_backslash_n(char **save, int n)
{
	char	*tmp;
	char	*line;

	line = NULL;
	line = ft_substr(*save, 0, n + 1);
	tmp = ft_substr(&(*save)[n + 1], 0, ft_strlen(&(*save)[n + 1]));
	free(*save);
	*save = tmp;
	return (line);
}

void	check_read(char *buf, int r)
{
	if (r >= 0)
		buf[r] = '\0';
	else
		buf[0] = 0;
}

char	*get_next_line(int fd, int mode)
{
	static char		*save;
	int				r;
	int				backslash_n;
	char			*buf;

	if (fd < 0 || BUFFER_SIZE <= 0 || mode == 1)
		return (free(save), save = NULL, NULL);
	backslash_n = -1;
	while (1)
	{
		if (save)
			backslash_n = ft_strchr_index(save, '\n');
		if (backslash_n >= 0)
			return (check_backslash_n(&save, backslash_n));
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buf)
			return (NULL);
		r = read(fd, buf, BUFFER_SIZE);
		check_read(buf, r);
		check_save(&save, buf);
		if ((r <= 0 || r < BUFFER_SIZE) && ft_strchr_index(save, '\n') == -1)
			return (dup_line(&save));
	}
	return (NULL);
}
