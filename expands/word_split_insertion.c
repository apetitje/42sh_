/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split_insertion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 14:57:27 by apetitje          #+#    #+#             */
/*   Updated: 2017/08/10 16:11:35 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void	copy_end_tab(t_token **tabl, size_t tab_size, t_token *tok_tab)
{
	size_t	j;

	j = 0;
	while (j < tab_size)
	{
		if ((*tabl)[j].type != TOKEN_VOID
				&& !(tok_tab[j].word = ft_strdup((*tabl)[j].word)))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		tok_tab[j].size = (*tabl)[j].size;
		tok_tab[j].type = (*tabl)[j].type;
		++j;
	}
	free_tok_tab(tabl);
}

void	copy_tab(t_token **tabl, t_token *to_copy,
		size_t *tab_size, size_t token_size)
{
	init_tok_tab(tabl, g_token_tab_size);
	*tab_size = 0;
	while (*tab_size < token_size)
	{
		(*tabl)[*tab_size].word = NULL;
		if (to_copy[*tab_size].word && to_copy[*tab_size].type != TOKEN_VOID
			&& !((*tabl)[*tab_size].word = ft_strdup(to_copy[*tab_size].word)))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		(*tabl)[*tab_size].size = to_copy[*tab_size].size;
		(*tabl)[*tab_size].type = to_copy[*tab_size].type;
		if (!to_copy[*tab_size].word)
			(*tabl)[*tab_size].type = TOKEN_VOID;
		ft_memdel((void **)&to_copy[*tab_size].word);
		to_copy[*tab_size].size = 0;
		to_copy[*tab_size].type = 0;
		++(*tab_size);
	}
}

void	split_and_insert(char **to_split, t_token **tok_tab,
		size_t *token_size, size_t *j)
{
	size_t	len;

	len = 0;
	while (*to_split && ((*to_split)[len] == ' ' || (*to_split)[len] == '\t'
				|| (*to_split)[len] == '\n'))
		++len;
	if (!(*to_split) || !(*to_split)[len])
		(*tok_tab)[*j].type = TOKEN_VOID;
	while (*to_split && (*to_split)[len])
		if ((*to_split)[len] == ' ' || (*to_split)[len] == '\t'
				|| (*to_split)[len] == '\n')
		{
			if ((*tok_tab)[*j].size)
			{
				++(*j);
				++(*token_size);
				if (*token_size >= g_token_tab_size - 2)
					extend_tok_tab(tok_tab, &g_token_tab_size,
							g_token_tab_size * 2);
			}
			++len;
		}
		else
			add_to_token(*to_split, &len, j, *tok_tab);
	ft_memdel((void **)to_split);
}
