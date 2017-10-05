/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 20:30:53 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 21:37:07 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static int	if_token_beggun(char *input, size_t *i, size_t *j, t_token *line)
{
	int		k;

	if (!ft_strcmp(line[*j].word, "&"))
	{
		if (input[*i] != '>')
		{
			++(*j);
			return (1);
		}
	}
	else
	{
		k = line[*j].size - 1;
		while (k)
		{
			if (!ft_isdigit(line[*j].word[k]))
			{
				++(*j);
				return (1);
			}
			--k;
		}
	}
	return (0);
}

static int	redirect_left(char *input, size_t *i, size_t *j, t_token *line)
{
	add_to_token(input, i, j, line);
	if (input[*i] == '<')
	{
		add_to_token(input, i, j, line);
		line[*j].type = TOKEN_HEREDOC;
		++(*j);
		if (heredoc_build(input, i, j, line))
			return (1);
	}
	else if (input[*i] == '>')
	{
		add_to_token(input, i, j, line);
		line[*j].type = TOKEN_REDIR_L;
	}
	else
		line[*j].type = TOKEN_REDIR_L;
	return (0);
}

int			redirect(char *input, size_t *i, size_t *j, t_token *line)
{
	if (line[*j].size)
		if (if_token_beggun(input, i, j, line))
			return (0);
	if (input[*i] != '<')
	{
		add_to_token(input, i, j, line);
		if (input[*i] == '>')
		{
			add_to_token(input, i, j, line);
			line[*j].type = TOKEN_DB_REDIR_R;
			if (input[*i] == '>')
				return (error_and_return("syntax error"));
		}
		else
			line[*j].type = TOKEN_REDIR_R;
	}
	else if (redirect_left(input, i, j, line))
		return (1);
	if (input[*i] == '&')
		add_to_token(input, i, j, line);
	*j += (line[*j].size) ? 1 : 0;
	return (0);
}
