/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_read_parse_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 12:15:21 by oyagci            #+#    #+#             */
/*   Updated: 2017/09/29 12:38:00 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*get_word(char *s)
{
	int i;

	i = 0;
	while (s[i] && !ft_isspace(s[i]))
		i += 1;
	return (ft_strndup(s, i));
}

char	**parse_variables(char *str, int ac)
{
	char	**vars;
	char	*word;
	int		i;

	ac = ac <= 0 ? 1 : ac;
	if (!(vars = ft_memalloc(sizeof(char *) * (ac + 1))))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	i = 0;
	while (i < ac - 1 && *str)
	{
		if (!(word = get_word(str)))
			exit_prog(EXIT_FAILURE, "Malloc error (get_word)\n");
		vars[i] = word;
		ft_memmove(str, str + ft_strlen(word),
			ft_strlen(str + ft_strlen(word)) + 1);
		while (*str && ft_isspace(*str))
			str += 1;
		i += 1;
	}
	if (i < ac && *str)
		if (!(vars[ac - 1] = ft_strdup(str)))
			exit_prog(EXIT_FAILURE, "Malloc error (parse_variables)\n");
	return (vars);
}
