/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:05:01 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 20:44:09 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static char	*find_word(char *input, size_t *i)
{
	size_t	len;
	char	*word;

	len = 0;
	word = NULL;
	while (input[*i + len] && (input[*i + len] == ' '
				|| input[*i + len] == '\t' || input[*i + len] == '\n'))
		++(*i);
	if (!input[*i + len])
		return (NULL);
	while (input[*i + len] && input[*i + len] != ' ' && input[*i + len] != '\t'
			&& input[*i + len] != '\n' && input[*i + len] != '|'
			&& input[*i + len] != ';' && input[*i + len] != '>'
			&& input[*i + len] != '<')
		++len;
	ft_asprintf(&word, "%.*s", len, input + *i);
	*i += len;
	return (word);
}

static int	free_and_return(char **sequence, int code, char **word)
{
	if (*sequence)
		free(*sequence);
	g_prompt_size = 3;
	free(*word);
	return (code);
}

static int	process_new_input(char **sequence, size_t *k, size_t *j,
		t_token *tok_tab)
{
	size_t	k_bck;

	if ((*sequence)[*k] == '`')
	{
		if (check_quotes(sequence, k, j, tok_tab))
			return (1);
	}
	else if ((*sequence)[*k] == '$')
	{
		k_bck = *k + 1;
		expand_var(tok_tab, *sequence, k, j);
		while ((*sequence)[k_bck] && (ft_isdigit((*sequence)[k_bck])
					|| ft_isalpha((*sequence)[k_bck])
					|| (*sequence)[k_bck] == '_' || (*sequence)[k_bck] == '?'))
			++k_bck;
		*k = k_bck;
	}
	else
		add_to_token(*sequence, k, j, tok_tab);
	return (0);
}

int			heredoc_build(char *input, size_t *i, size_t *j, t_token *tok_tab)
{
	char	*word;
	char	*sequence;
	size_t	k;

	if ((word = find_word(input, i)) == NULL)
		return (ft_dprintf(2, "42sh: syntax error\n"));
	if (!(sequence = ft_strdup("")))
		exit_prog(EXIT_FAILURE, "Malloc error (heredoc_build)\n");
	while (ft_strcmp(sequence, word))
	{
		k = 0;
		ft_memdel((void **)&sequence);
		g_prompt_size = 2;
		sequence = read_line(&g_hist);
		if (!sequence || !ft_strcmp(sequence, word)
				|| !ft_strcmp(sequence, "EOF"))
			break ;
		while (sequence[k])
			if (process_new_input(&sequence, &k, j, tok_tab))
				return (free_and_return(&sequence, 1, &word));
		k = 0;
		add_to_token("\n", &k, j, tok_tab);
	}
	return (free_and_return(&sequence, ((sequence) ? 0 : 1), &word));
}
