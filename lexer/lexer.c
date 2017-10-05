/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 15:37:20 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/04 17:23:12 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static int	end_lexing(size_t *j, t_token *tok_tab)
{
	if (tok_tab[*j].size)
		++(*j);
	tok_tab[*j].type = TOKEN_EOF;
	tok_tab[*j].size = 3;
	if (!(tok_tab[*j].word = ft_strdup("EOF")))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	g_prompt_size = 3;
	return (0);
}

void		process_input_suite(char **input, size_t *i, size_t *j,
		t_token *tok_tab)
{
	if ((*input)[*i] == '=' && (*i != 0) && (*input)[*i - 1] != '\\')
	{
		tok_tab[*j].type = (tok_tab[*j].size) ? TOKEN_VAR : tok_tab[*j].type;
		add_to_token(*input, i, j, tok_tab);
	}
	else
		add_to_token(*input, i, j, tok_tab);
}

int			process_input(char **input, size_t *i, size_t *j, t_token *tok_tab)
{
	int		ret;

	ret = 0;
	if ((*input)[*i] == '\\')
		ret = (echap(input, i, j, tok_tab)) ? 1 : ret;
	else if ((*input)[*i] == '"' || (*input)[*i] == '\'' || (*input)[*i] == '`')
		ret = (check_quotes(input, i, j, tok_tab)) ? 1 : ret;
	else if ((*input)[*i] == '(')
		ret = (check_parenthesis(input, i, j, tok_tab)) ? 1 : ret;
	else if (((*input)[*i] == '<' || (*input)[*i] == '>'))
		ret = (redirect(*input, i, j, tok_tab)) ? 1 : ret;
	else if ((*input)[*i] == '|' && (*input)[*i + 1] == '|')
		ret = token_or(*input, i, j, tok_tab);
	else if ((*input)[*i] == '&' && (*input)[*i + 1] != '>')
		ret = (((*input)[*i + 1] == '&') ? token_and(*input, i, j, tok_tab)
				: token_esper(*input, i, j, tok_tab));
	else if (((*input)[*i] == ';' || (*input)[*i] == '|' || (*input)[*i] == ' '
				|| (*input)[*i] == '\t' || (*input)[*i] == '\n'))
		ret = split_tokens(*input, i, j, tok_tab);
	else if ((*input)[*i] == ')')
		return (error_and_return("syntax error near unexpected token ')'"));
	else
		process_input_suite(input, i, j, tok_tab);
	return (ret);
}

int			parse_line(char **input, t_token **tok_tab, size_t *token_size)
{
	size_t	i;
	size_t	j;
	int		res;

	i = 0;
	j = 0;
	res = 0;
	while ((*input)[i])
	{
		if (process_input(input, &i, &j, *tok_tab))
		{
			g_exit_status = 1;
			return (1);
		}
		(j >= *token_size - 10) ? extend_tok_tab(tok_tab,
				token_size, *token_size * 2) : 0;
	}
	return (end_lexing(&j, *tok_tab));
}
