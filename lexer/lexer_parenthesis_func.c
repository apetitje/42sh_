/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parenthesis_func.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:03:20 by apetitje          #+#    #+#             */
/*   Updated: 2017/09/29 16:14:33 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int			is_bracket(char *input, size_t i)
{
	if ((i == 0 || input[i - 1] != '\\') && input[i] == '(')
		return (1);
	if ((i == 0 || input[i - 1] != '\\') && input[i] == ')')
		return (-1);
	return (0);
}

int			parenthesis(char **input, size_t *i, size_t *j, t_token *tok_tab)
{
	int		brackets;

	brackets = 1;
	while ((*input)[*i] && brackets > 0)
	{
		if (!(brackets += is_bracket(*input, *i)))
			break ;
		if ((*input)[*i] == '"' || (*input)[*i] == '\'' || (*input)[*i] == '`')
		{
			if (check_quotes(input, i, j, tok_tab))
				return (1);
		}
		else
			add_to_token(*input, i, j, tok_tab);
	}
	if (brackets != 0)
	{
		ft_memdel((void **)input);
		*input = wait_for_bracket(i, j, tok_tab, &brackets);
		return ((*input) ? 0 : 1);
	}
	++(*i);
	if (tok_tab[*j].size)
		tok_tab[(*j)++].type = TOKEN_SUBSH;
	return (0);
}

int			check_parenthesis(char **input, size_t *i, size_t *j,
		t_token *tok_tab)
{
	if (tok_tab[*j].size)
		++(*j);
	++(*i);
	return (parenthesis(input, i, j, tok_tab));
}
