/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:40:22 by malancar          #+#    #+#             */
/*   Updated: 2023/07/08 16:14:51 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*join(char *s1, char *s2)
{
	int		i;
	int		j;
	int		a;
	int		len;
	char	*s3;

	i = 0;
	j = 0;
	a = 0;
	len = (ft_strlen(s1)) + (ft_strlen(s2));
	s3 = malloc(sizeof(char) * (len + 1));
	if (!s3)
		return (0);
	while (s1[i])
		s3[i++] = s1[a++];
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	free(s1);
	free(s2);
	return (s3);
}

char	*ft_substr(char	*s, int start, int len)
{
	char	*s2;
	int		i;

	i = 0;
	if (start >= ft_strlen(s))
	{
		s2 = malloc(sizeof(char) * 1);
		if (!s2)
			return (NULL);
		s2[i] = '\0';
		return (s2);
	}
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	s2 = malloc(sizeof(char) * len + 1);
	if (!s2)
		return (NULL);
	while (s[start + i] && i < len)
	{
		s2[i] = s[start + i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*dup_line(char **s)
{
	char	*s1;
	int		i;

	i = 0;
	s1 = NULL;
	if (!*s)
		return (NULL);
	if (**s == 0)
	{
		free(*s);
		*s = NULL;
		return (NULL);
	}
	if (*s)
	{
		i = ft_strlen(*s);
		s1 = malloc(sizeof(char) * (i + 1));
		if (!s1)
			return (NULL);
		ft_memmove(s1, *s, i);
		free(*s);
		*s = NULL;
		s1[i] = '\0';
	}
	return (s1);
}
