/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:27:38 by malancar          #+#    #+#             */
/*   Updated: 2023/07/19 18:21:16 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	len;

	len = ft_strlen(str);
	if (write(fd, str, len) == -1)
	{
		perror("write");
	}
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = ft_strlen(dest);
	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2, char c)
{
	int		i;
	char	*s3;

	i = ft_strlen(s1);
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1 + 1));
	if (!s3)
		return (NULL);
	s3[0] = '\0';
	ft_strcat(s3, s1);
	s3[i] = c;
	s3[i + 1] = '\0';
	ft_strcat(s3, s2);
	return (s3);
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	int		i;

	if (!s1)
		return (NULL);
	i = 0;
	s2 = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
