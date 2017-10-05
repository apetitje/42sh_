/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 18:55:00 by apetitje          #+#    #+#             */
/*   Updated: 2017/03/04 17:02:02 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int	ft_count_words(char const *s, char c)
{
	int		i;
	int		nb_words;

	i = 0;
	nb_words = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			nb_words++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (nb_words);
}

static int	ft_word_len(char const *str, int index, char c)
{
	int		len;

	len = 0;
	while (str[index] && str[index] == c)
		index++;
	while (str[index] && str[index] != c)
	{
		index++;
		len++;
	}
	return (len);
}

static void	ft_fill_tab(char *tab, char const *s, char c, int *index)
{
	int		i;

	i = 0;
	while (s[*index] && s[*index] == c)
		(*index)++;
	while (s[*index] && s[*index] != c)
	{
		tab[i] = s[*index];
		(*index)++;
		i++;
	}
	tab[i] = '\0';
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		nb_words;
	int		index;
	int		tab_i;
	int		word_len;

	index = 0;
	tab_i = 0;
	if (!s)
		return (NULL);
	nb_words = ft_count_words(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (nb_words + 1))))
		return (NULL);
	tab[nb_words] = NULL;
	while (tab_i < nb_words)
	{
		word_len = (ft_word_len(s, index, c));
		if (!(tab[tab_i] = (char *)malloc(sizeof(char) * (word_len + 1))))
			return (NULL);
		ft_fill_tab(tab[tab_i], s, c, &index);
		tab_i++;
	}
	return (tab);
}
