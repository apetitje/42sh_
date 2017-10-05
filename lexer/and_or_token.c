/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 21:34:20 by apetitje          #+#    #+#             */
/*   Updated: 2017/06/09 14:30:43 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		token_and(char *input, size_t *i, size_t *j, t_token *line)
{
	if (input[*i + 2] == '&')
		return (error_and_return("syntax error : unexpected token '&'"));
	if (line[*j].size)
		++(*j);
	line[*j].type = TOKEN_AND;
	add_to_token(input, i, j, line);
	add_to_token(input, i, j, line);
	++(*j);
	return (0);
}

int		token_or(char *input, size_t *i, size_t *j, t_token *line)
{
	if (input[*i + 2] == '|')
		return (error_and_return("syntax error : unexpected token '|'"));
	if (line[*j].size)
		++(*j);
	line[*j].type = TOKEN_OR;
	add_to_token(input, i, j, line);
	add_to_token(input, i, j, line);
	++(*j);
	return (0);
}
