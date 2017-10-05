/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal_sub.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 15:27:08 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 20:56:17 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	add_to_content(char **content, size_t *c_size, size_t *len,
		const char inp)
{
	if (*c_size)
		*content = ft_realloc(*content, *c_size + 2, *c_size + 1);
	else
		*content = ft_memalloc(2);
	if (!*content)
		exit_prog(EXIT_FAILURE, "Malloc error (remove_db_quotes)\n");
	(*content)[*c_size] = inp;
	++(*c_size);
	++(*len);
}

void	remove_db_quotes(char **word, size_t *i, char **content, char **end)
{
	size_t	len;
	size_t	size;

	len = 0;
	*content = NULL;
	size = 0;
	while ((*word)[*i + len] && (*word)[*i + len] != '"')
	{
		if ((*word)[*i + len] == '\\' && ((*word)[*i + len + 1] == '"'
					|| (*word)[*i + len + 1] == '\\'))
		{
			++len;
			add_to_content(content, &size, &len, (*word)[*i + len]);
		}
		else
			add_to_content(content, &size, &len, (*word)[*i + len]);
	}
	if ((*word)[*i + len] && !(*end = ft_strdup(*word + *i + 1 + len)))
		exit_prog(EXIT_FAILURE, "Malloc error (remove_quotes)\n");
}
