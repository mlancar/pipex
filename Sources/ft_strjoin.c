/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:48:00 by malancar          #+#    #+#             */
/*   Updated: 2023/06/12 19:49:14 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

/*int	main(int ac, char **av)
{
	char	*str;

	if (ac == 4)
	{
		str = ft_strjoin(av[1], av[2], av[3][0]);
		printf("s3 = %s\n", str);
		free(str);
	}
	return (0);

}*/
