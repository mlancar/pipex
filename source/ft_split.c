/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:07:59 by malancar          #+#    #+#             */
/*   Updated: 2023/07/13 19:42:34 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "pipex.h"

int	len_words(char *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i] && str[i] != c)
	{
		len++;
		if (str[i])
			i++;
	}
	return (len);
}

int	nbr_words(char *str, char c)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] && str[i] != c)
		{
			while (str[i] && str[i] != c)
				i++;
			nbr++;
		}
		if (str[i])
			i++;
	}
	return (nbr);
}

int	fill_tab(char *str, int i, char ***tab, char c)
{
	int	k;
	int	j;

	j = 0;
	while (str[i])
	{
		if (str[i] && str[i] != c)
		{
			k = 0;
			(*tab)[j] = malloc(sizeof(char) * (len_words(&str[i], c) + 1));
			if (!(*tab))
				return (0);
			while (str[i] && str[i] != c)
			{
				(*tab)[j][k] = str[i];
				i++;
				k++;
			}
			(*tab)[j++][k] = '\0';
		}
		if (str[i])
			i++;
	}
	(*tab)[j] = NULL;
	return (1);
}

char	**ft_split(char *str, char c)
{
	int		i;
	char	**tab;

	i = 0;
	tab = malloc(sizeof(char *) * (nbr_words(str, c) + 1));
	if (!tab)
		return (NULL);
	while (str[i] && str[i] == c)
		i++;
	if (fill_tab(str, i, &tab, c) == 0)
		return (free_tab(tab), NULL);
	return (tab);
}

/*int	main(int ac, char **av)
{
	int		i;
	char	**tab;

	(void)ac;
	i = 0;
	tab = ft_split(av[1], av[2][0]);
	while (tab[i])
	{
		printf("tab = %s\n", tab[i]);
		i++;
	}
	free_tab(tab);
}*/