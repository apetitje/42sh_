/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 15:27:08 by apetitje          #+#    #+#             */
/*   Updated: 2017/09/29 13:50:53 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	quote_rem_vars(char **begin, char **end,
		char **content, int code)
{
	if (!code)
	{
		*begin = NULL;
		*end = NULL;
		*content = NULL;
	}
	else
	{
		ft_memdel((void **)begin);
		ft_memdel((void **)end);
		ft_memdel((void **)content);
	}
	return (0);
}

void		remove_quotes(char **word, size_t *i, char quote)
{
	char	*begin;
	char	*end;
	char	*content;
	size_t	len;

	len = quote_rem_vars(&begin, &end, &content, 0);
	ft_asprintf(&begin, "%.*s", *i, *word);
	++(*i);
	if (quote == '"')
		remove_db_quotes(word, i, &content, &end);
	else
	{
		while (quote != '\\' && (*word)[*i + len] && (*word)[*i + len] != quote)
			++len;
		if ((*word)[*i + len])
			len = (quote == '\\' && (*word)[*i]) ? 1 : len;
		ft_asprintf(&content, "%.*s", len, *word + *i);
		len += (quote != '\\' && (*word)[*i + len]) ? 1 : 0;
		if ((*word)[*i + len] && !(end = ft_strdup(*word + *i + len)))
			exit_prog(EXIT_FAILURE, "Malloc error (remove_quotes)\n");
	}
	ft_memdel((void **)word);
	*i += (content && *content) ? ft_strlen(content) - 1 : -1;
	ft_asprintf(word, "%s%s%s", begin, content, end);
	quote_rem_vars(&begin, &end, &content, 1);
}

static void	quote_rem_by_char(t_token *tok_tab, size_t *i)
{
	if (tok_tab->word[*i] == '"' || tok_tab->word[*i] == '\''
			|| tok_tab->word[*i] == '\\' || tok_tab->word[*i] == '`')
	{
		remove_quotes(&tok_tab->word, i, tok_tab->word[*i]);
		if (!(tok_tab->word))
		{
			tok_tab->size = 0;
			if (!(tok_tab->word = ft_strdup("")))
				exit_prog(EXIT_FAILURE, "Malloc error (quote_rem_by_char)\n");
			tok_tab->type = TOKEN_NULL;
			*i = 0;
		}
		else
			tok_tab->size = ft_strlen(tok_tab->word);
	}
	else
		++(*i);
}

void		quote_removal(t_token *tok_tab, size_t token_size)
{
	size_t	j;
	size_t	i;

	j = 0;
	while (j < token_size)
	{
		i = 0;
		if (j == 0 || tok_tab[j - 1].type != TOKEN_HEREDOC)
		{
			if (tok_tab[j].type == TOKEN_EXPANDED)
				tok_tab[j].type = TOKEN_STR;
			else if (tok_tab[j].type != TOKEN_VOID)
			{
				if (tok_tab[j].type == TOKEN_VAR_EXP)
					tok_tab[j].type = TOKEN_STR;
				while (tok_tab[j].word[i])
					quote_rem_by_char(tok_tab + j, &i);
			}
		}
		++j;
	}
}
