/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:16:03 by apetitje          #+#    #+#             */
/*   Updated: 2017/09/29 18:42:04 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static void	init_bq_vars(char **line, char **end, char **begin, char **command)
{
	*command = NULL;
	*begin = NULL;
	*end = NULL;
	*line = NULL;
}

static void	free_bq_vars(char **line, char **end, char **begin, char **command)
{
	ft_memdel((void **)end);
	ft_memdel((void **)begin);
	ft_memdel((void **)command);
	ft_memdel((void **)line);
}

void		expand_bq(t_token *tok_tab, size_t *i)
{
	char	*command;
	size_t	len;
	char	*line;
	char	*begin;
	char	*end;

	len = 0;
	init_bq_vars(&line, &end, &begin, &command);
	ft_asprintf(&begin, "%.*s", *i, tok_tab->word);
	++(*i);
	while (tok_tab->word[*i + len] && (tok_tab->word[*i + len] != '`' ||
				tok_tab->word[*i + len - 1] == '\\'))
		++len;
	ft_asprintf(&end, "%s", tok_tab->word + *i + len + 1);
	ft_asprintf(&command, "%.*s", len, tok_tab->word + *i);
	redir_command_bq(command, &line);
	if (line && *line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	ft_memdel((void **)&tok_tab->word);
	tok_tab->size = ft_asprintf(&tok_tab->word, "%s%s%s", begin, line, end);
	(*i) = ((begin) ? ft_strlen(begin) : 0) + 1;
	if (line)
		(*i) += ft_strlen(line);
	(*i) -= 1;
	free_bq_vars(&line, &end, &begin, &command);
}
