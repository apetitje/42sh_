/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 16:53:52 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 11:55:35 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int			b_quote(char **input, size_t *i, size_t *j, t_token *tok_tab)
{
	while ((*input)[*i] && ((*input)[*i] != '`' || (*i > 0 &&
					(*input)[*i - 1] == '\\')))
		add_to_token(*input, i, j, tok_tab);
	if ((*input)[*i] != '`')
	{
		ft_memdel((void **)input);
		*input = wait_for_character(i, '`', j, tok_tab);
		if (!*input)
			return (1);
		return (0);
	}
	add_to_token(*input, i, j, tok_tab);
	return (0);
}

int			s_quote(char **input, size_t *i, size_t *j, t_token *tok_tab)
{
	while ((*input)[*i] && (*input)[*i] != '\'')
		add_to_token(*input, i, j, tok_tab);
	if ((*input)[*i] != '\'')
	{
		ft_memdel((void **)input);
		*input = wait_for_character(i, '\'', j, tok_tab);
		if (!*input)
			return (1);
		return (0);
	}
	add_to_token(*input, i, j, tok_tab);
	return (0);
}

int			d_quote(char **input, size_t *i, size_t *j, t_token *tok_tab)
{
	while ((*input)[*i] && (*input)[*i] != '"')
	{
		if ((*input)[*i] == '`')
		{
			add_to_token(*input, i, j, tok_tab);
			if (b_quote(input, i, j, tok_tab))
				return (1);
		}
		else if ((*input)[*i] == '\\')
			echap(input, i, j, tok_tab);
		else
			add_to_token(*input, i, j, tok_tab);
	}
	if ((*input)[*i] != '"')
	{
		ft_memdel((void **)input);
		*input = wait_for_character(i, '"', j, tok_tab);
		if (!*input)
			return (1);
		return (0);
	}
	add_to_token(*input, i, j, tok_tab);
	return (0);
}

static void	find_quote_type(char quote,
		int (**f)(char **, size_t *, size_t *, t_token *))
{
	if (quote == '"')
		*f = &d_quote;
	else if (quote == '\'')
		*f = &s_quote;
	else if (quote == '`')
		*f = &b_quote;
}

int			check_quotes(char **input, size_t *i, size_t *j, t_token *tok_tab)
{
	int			res;
	t_tok_type	type;
	int			(*f)(char **, size_t *, size_t *, t_token *);

	res = 0;
	add_to_token(*input, i, j, tok_tab);
	type = 1;
	find_quote_type((*input)[*i - 1], &f);
	res = f(input, i, j, tok_tab);
	return (res);
}
