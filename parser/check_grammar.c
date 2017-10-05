/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grammar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 14:10:01 by apetitje          #+#    #+#             */
/*   Updated: 2017/09/29 20:40:54 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int	check_grammar(t_token *tok_tab)
{
	int		i;

	i = -1;
	while (tok_tab[++i].type != TOKEN_EOF)
		if ((!tok_tab[i].size || (tok_tab[i].type != TOKEN_EOF
				&& tok_tab[i].type != TOKEN_STR && tok_tab[i].type != TOKEN_VAR
				&& tok_tab[i].type != TOKEN_SEMI
				&& tok_tab[i].type != TOKEN_REDIR_R
				&& tok_tab[i].type != TOKEN_REDIR_L
				&& tok_tab[i].type != TOKEN_DB_REDIR_R
				&& tok_tab[i].type != TOKEN_HEREDOC
				&& tok_tab[i].type != TOKEN_PIPE
				&& tok_tab[i].type != TOKEN_OR
				&& tok_tab[i].type != TOKEN_AND
				&& tok_tab[i].type != TOKEN_BQ
				&& tok_tab[i].type != TOKEN_ESPER
				&& tok_tab[i].type != TOKEN_SUBSH))
				|| (tok_tab[i].type == TOKEN_SUBSH
				&& (tok_tab[i + 1].type == TOKEN_STR
				|| tok_tab[i + 1].type == TOKEN_VAR
				|| tok_tab[i + 1].type == TOKEN_SUBSH
				|| tok_tab[i + 1].type == TOKEN_BQ
				|| tok_tab[i + 1].type == TOKEN_NULL)))
			return (error_and_return("syntax error"));
	return (0);
}
