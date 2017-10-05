/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 14:01:13 by oyagci            #+#    #+#             */
/*   Updated: 2017/09/04 11:31:06 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			quote_words(char **event)
{
	char	*quoted;

	escape_single_quotes(event);
	if (NULL == (quoted = ft_strnew(ft_strlen(*event) + 2)))
		exit_prog(EXIT_FAILURE, "Malloc error (quote_words)\n");
	quoted[0] = '\'';
	ft_strcat(quoted, *event);
	ft_strcat(quoted, "'");
	free(*event);
	*event = quoted;
}

void			quote_current_word(char **str, int *i)
{
	char	*tmp;

	if (!(tmp = ft_strnew(ft_strlen(*str) + 2)))
		exit_prog(EXIT_FAILURE, "Malloc error (quote_current_word)");
	ft_strcat(tmp, *str);
	ft_memmove(tmp + *i + 1, tmp + *i, ft_strlen(tmp + *i + 1) + 1);
	tmp[*i] = '\'';
	*i += 1;
	while (1)
	{
		if (!(!ft_isspace(tmp[*i]) && tmp[*i]))
			break ;
		*i += 1;
	}
	ft_memmove(tmp + *i + 1, tmp + *i, ft_strlen(tmp + *i + 1) + 1);
	tmp[*i] = '\'';
	*i += 1;
	free(*str);
	*str = tmp;
}

void			quote_split(char **event)
{
	int		i;

	escape_single_quotes(event);
	i = 0;
	while (1)
	{
		if (!ft_isspace((*event)[i]))
			quote_current_word(event, &i);
		else
			i += 1;
		if (!(*event)[i])
			break ;
	}
}
