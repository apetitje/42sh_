/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tab_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 13:32:08 by apetitje          #+#    #+#             */
/*   Updated: 2017/08/02 16:12:00 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void	extend_tok_tab(t_token **tok_tab, size_t *old_size, size_t new_size)
{
	t_token *tmp;
	size_t	i;

	i = 0;
	tmp = *tok_tab;
	init_tok_tab(tok_tab, new_size);
	while (i < *old_size)
	{
		(*tok_tab)[i].word = tmp[i].word;
		(*tok_tab)[i].size = tmp[i].size;
		(*tok_tab)[i].type = tmp[i].type;
		++i;
	}
	*old_size = new_size;
	free(tmp);
}

void	init_tok_tab(t_token **tok_tab, size_t size)
{
	size_t	i;

	i = 0;
	if (!(*tok_tab = malloc(sizeof(t_token) * size)))
		exit_prog(EXIT_FAILURE, "Malloc error.\n");
	while (i < size)
	{
		(*tok_tab)[i].word = NULL;
		(*tok_tab)[i].size = 0;
		(*tok_tab)[i].type = 0;
		++i;
	}
}

void	free_tok_tab_content(t_token *tok_tab)
{
	size_t	i;

	if (!tok_tab)
		return ;
	i = 0;
	while (tok_tab[i].size || tok_tab[i].type)
	{
		ft_memdel((void **)&(tok_tab[i].word));
		tok_tab[i].size = 0;
		tok_tab[i].type = 0;
		++i;
	}
}

void	free_tok_tab(t_token **tok_tab)
{
	if (!*tok_tab)
		return ;
	free_tok_tab_content(*tok_tab);
	free(*tok_tab);
	*tok_tab = NULL;
}
