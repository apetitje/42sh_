/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 19:50:01 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 21:05:22 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static int	find_char(const char in, char *out)
{
	if (in == '\'')
		*out = '\'';
	else if (in == '"')
		*out = '"';
	else
		return (1);
	return (0);
}

static int	test_for_matching(t_token **tok_tab, size_t *i, size_t *j,
		char character)
{
	++(*i);
	if (character == '"')
	{
		while ((*tok_tab)[*j].word[*i] && (*tok_tab)[*j].word[*i] != character)
		{
			if ((*tok_tab)[*j].word[*i] == '`')
				expand_bq(*tok_tab + *j, i);
			else if ((*tok_tab)[*j].word[*i] == '\\')
				(*i) += (((*tok_tab)[*j].word[*i + 1]) ? 2 : 1);
			else if ((*tok_tab)[*j].word[*i] != '$')
				++(*i);
			else if (expand_var(*tok_tab, (*tok_tab)[*j].word, i, j))
				break ;
		}
	}
	else
		while ((*tok_tab)[*j].word[*i] && (*tok_tab)[*j].word[*i] != character)
			++(*i);
	if ((*tok_tab)[*j].word[*i] && (*tok_tab)[*j].word[++(*i)])
		return (0);
	return (1);
}

static void	process_by_char_end(size_t *i, size_t *j,
		t_token **tok_tab, int *flag)
{
	if ((*tok_tab)[*j].word[*i] == '`')
	{
		expand_bq(*tok_tab + *j, i);
		if ((*tok_tab)[*j].size)
		{
			(*tok_tab)[*j].type = TOKEN_EXPANDED;
			*flag = 1;
		}
		else
		{
			(*tok_tab)[*j].type = TOKEN_VOID;
			*i = 0;
		}
	}
	else if ((*tok_tab)[*j].word[*i] == '\\' && (*tok_tab)[*j].word[*i + 1])
		(*i) += 2;
	else
		++(*i);
}

static void	process_by_char(size_t *i, size_t *j,
		t_token **t_tab, int *flag)
{
	char	character;

	character = 0;
	while ((*t_tab)[*j].type != TOKEN_VOID && (*t_tab)[*j].word[*i])
	{
		if (!find_char((*t_tab)[*j].word[*i], &character))
			test_for_matching(t_tab, i, j, character);
		else
		{
			if (*i != 0 && (*t_tab)[*j].word[*i] == '~'
					&& ((((*t_tab)[*j].type == TOKEN_VAR
						&& ((*t_tab)[*j].word[*i - 1] == ':'
						|| (*t_tab)[*j].word[*i - 1] == '=')))
						|| (*t_tab)[*j].word[*i - 1] == '{'))
				expand_tilde((*t_tab)[*j].word, *t_tab, i, j);
			else if ((*t_tab)[*j].word[*i] == '$')
			{
				if (expand_var(*t_tab, (*t_tab)[*j].word, i, j))
					break ;
				*flag = 1;
			}
			else
				process_by_char_end(i, j, t_tab, flag);
		}
	}
}

int			expands(t_token **tok_tab, size_t *token_size)
{
	size_t	i;
	size_t	j;
	int		flag;

	j = 0;
	flag = 0;
	while (j < *token_size)
	{
		i = 0;
		if (j == 0 || (*tok_tab)[j - 1].type != TOKEN_HEREDOC)
		{
			if ((*tok_tab)[j].word[i] == '~')
				expand_tilde((*tok_tab)[j].word, *tok_tab, &i, &j);
			else
				process_by_char(&i, &j, tok_tab, &flag);
		}
		++j;
	}
	if (flag)
		word_splitting(tok_tab, token_size);
	expand_glob(tok_tab, token_size);
	quote_removal(*tok_tab, *token_size);
	return (0);
}
