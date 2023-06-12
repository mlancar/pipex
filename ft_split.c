/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:07:59 by malancar          #+#    #+#             */
/*   Updated: 2023/06/12 18:15:23 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
}

int	len_word(char *str, char c)
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
		i++;
	}
	return (len);
}

int	nbr_word(char *str, char c)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] != c)
		{
			while (str[i] && str[i] != c)
				i++;
			nbr++;
		}
		if (str[i] == c)
			i++;
	}
	return (nbr);
}

char	**ft_split(char *str, char c)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (nbr_word(str, c) + 1));
	if (!tab)
		return (NULL);
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		k = 0;
		tab[j] = malloc(sizeof(char) * (len_word(&str[i], c) + 1));
		if (!tab[j])
			return (free_tab(tab), NULL);
		while (str[i] && str[i] != c)
		{
			tab[j][k] = str[i];
			k++;
			if (str[i])
				i++;
		}
		tab[j][k] = '\0';
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

/*int	main(int ac, char **av)
{
	int		i;
	char	**tab;

	i = 0;
	if (ac == 3)
	{	
		tab = ft_split(av[1], av[2][0]);
		while (tab[i])
		{
			printf("%s\n", tab[i]);
			i++;
		}
		free_tab(tab);
		free(tab);
	}
	return (0);
}*/
