/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:54:13 by apetitje          #+#    #+#             */
/*   Updated: 2017/09/30 19:33:01 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static void	split_words(t_token **tok_tab, size_t *j,
		size_t *token_size, size_t *i)
{
	char	*to_split;
	t_token *t_end_copy;
	size_t	t_end_size;

	to_split = NULL;
	copy_tab(&t_end_copy, *tok_tab + *j + 1, &t_end_size, *token_size - *j - 1);
	++(*i);
	if (!(to_split = ft_strdup((*tok_tab)[*j].word)))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	ft_memdel((void **)&(*tok_tab)[*j].word);
	(*tok_tab)[*j].size = 0;
	split_and_insert(&to_split, tok_tab, token_size, j);
	if (!(*tok_tab)[*j].size)
	{
		if (*j)
			--(*j);
		--(*token_size);
	}
	*i = (*tok_tab)[*j].size;
	copy_end_tab(&t_end_copy, t_end_size, *tok_tab + *j + 1);
}

void		word_splitting(t_token **tok_tab, size_t *token_size)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < *token_size)
	{
		if ((*tok_tab)[j].type == TOKEN_EXPANDED ||
				(*tok_tab)[j].type == TOKEN_VAR_EXP)
		{
			i = 0;
			split_words(tok_tab, &j, token_size, &i);
		}
		++j;
	}
}
