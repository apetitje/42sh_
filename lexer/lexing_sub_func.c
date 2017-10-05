/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_sub_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 18:11:27 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 11:54:58 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int			token_esper(char *input, size_t *i, size_t *j, t_token *tok_tab)
{
	if (*j != 0 && tok_tab[*j - 1].type == TOKEN_SEMI)
		return (error_and_return("syntax error near unexpected token '&'"));
	if (tok_tab[*j].size)
		++(*j);
	tok_tab[*j].type = TOKEN_ESPER;
	add_to_token(input, i, j, tok_tab);
	++(*j);
	return (0);
}

int			add_to_token(char *input, size_t *i, size_t *j, t_token *tok_tab)
{
	if (input[*i])
	{
		if (tok_tab[*j].size)
			tok_tab[*j].word = ft_realloc(tok_tab[*j].word,
					tok_tab[*j].size + 2,
					tok_tab[*j].size + 1);
		else
			tok_tab[*j].word = ft_memalloc(2);
		if (tok_tab[*j].word == NULL)
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		tok_tab[*j].word[tok_tab[*j].size] = input[*i];
		tok_tab[*j].size += 1;
		++(*i);
	}
	return (0);
}

int			split_tokens(char *input, size_t *i, size_t *j, t_token *tok_tab)
{
	if (tok_tab[*j].size)
		++(*j);
	if (input[*i] == ';')
	{
		if (*j == 0 || (*j != 0 && (tok_tab[*j - 1].type == TOKEN_ESPER
				|| tok_tab[*j - 1].type == TOKEN_SEMI)))
			return (error_and_return("syntax error near unexpected token ';'"));
		tok_tab[*j].type = TOKEN_SEMI;
		add_to_token(input, i, j, tok_tab);
		++(*j);
	}
	else if (input[*i] == '|')
	{
		tok_tab[*j].type = TOKEN_PIPE;
		add_to_token(input, i, j, tok_tab);
		++(*j);
	}
	else
		++(*i);
	tok_tab[*j].type = TOKEN_STR;
	return (0);
}

int			echap(char **input, size_t *i, size_t *j, t_token *tok_tab)
{
	char	*sequence;

	if (!(*input)[*i + 1] && g_interactive)
	{
		ft_memdel((void **)input);
		sequence = NULL;
		g_prompt_size = 2;
		*input = read_line(&g_hist);
		g_prompt_size = 3;
		*i = 0;
		if (!*input || !ft_strcmp(*input, "EOF"))
			return (1);
		return (0);
	}
	else
	{
		add_to_token(*input, i, j, tok_tab);
		add_to_token(*input, i, j, tok_tab);
	}
	g_prompt_size = 3;
	return (0);
}
