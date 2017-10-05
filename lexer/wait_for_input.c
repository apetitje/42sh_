/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 22:10:26 by apetitje          #+#    #+#             */
/*   Updated: 2017/09/29 19:42:58 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static int	double_quote_parse(char **sequence, size_t *k, size_t *j,
		t_token *tok_tab)
{
	int		ret;

	ret = 0;
	if ((*sequence)[*k] == '`')
		ret = b_quote(sequence, k, j, tok_tab);
	else if ((*sequence)[*k] == '\\')
		echap(sequence, k, j, tok_tab);
	else
		add_to_token(*sequence, k, j, tok_tab);
	if (ret)
		return (1);
	return (0);
}

static char	*s_init(size_t *k, size_t *j, t_token *tok_tab)
{
	char	*sequence;
	int		ret;

	*k = 0;
	sequence = NULL;
	add_to_token("\n", k, j, tok_tab);
	g_prompt_size = 2;
	*k = 0;
	if (g_interactive)
		sequence = read_line(&g_hist);
	else
	{
		ret = get_next_line((g_subsh_fd) ? g_subsh_fd : 0, &sequence);
		if (ret < 1)
			ft_memdel((void **)&sequence);
	}
	return (sequence);
}

char		*wait_for_character(size_t *i, char character,
		size_t *j, t_token *tok_tab)
{
	char	*sequence;
	size_t	k;

	while (1)
	{
		if (!(sequence = s_init(&k, j, tok_tab)) || !ft_strcmp(sequence, "EOF"))
			return (error_in_waiting(&sequence));
		while (sequence[k] && (sequence[k] != character
					|| (character == '`' && k != 0 && sequence[k - 1] == '\\')))
		{
			if (character != '"')
				add_to_token(sequence, &k, j, tok_tab);
			else if (double_quote_parse(&sequence, &k, j, tok_tab))
				return (NULL);
		}
		if (sequence[k] == character)
		{
			add_to_token(sequence, &k, j, tok_tab);
			*i = k;
			return (sequence);
		}
		ft_memdel((void **)&sequence);
	}
}

char		*wait_for_bracket(size_t *i, size_t *j, t_token *tok_tab,
		int *brackets)
{
	char	*s;
	size_t	k;

	while (1)
	{
		if (!(s = s_init(&k, j, tok_tab)) || !ft_strcmp(s, "EOF"))
			return (error_in_waiting(&s));
		while (s[k] && *brackets)
		{
			if (!(*brackets += is_bracket(s, k)))
				break ;
			if (s[k] != '"' && s[k] != '\'' && s[k] != '`')
				add_to_token(s, &k, j, tok_tab);
			else if (check_quotes(&s, &k, j, tok_tab))
				return (error_in_waiting(&s));
		}
		if (!(*brackets))
		{
			if (tok_tab[*j].size)
				tok_tab[(*j)++].type = TOKEN_SUBSH;
			*i = k + 1;
			return (s);
		}
		ft_memdel((void **)&s);
	}
}
