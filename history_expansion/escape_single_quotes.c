/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_single_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 10:02:06 by oyagci            #+#    #+#             */
/*   Updated: 2017/10/03 16:33:10 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			escape_single_quotes(char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (1)
	{
		if ((*str)[i] == '\'')
		{
			if (!(tmp = ft_strnew(ft_strlen(*str) + 3)))
				exit_prog(EXIT_FAILURE, "Malloc error\n");
			ft_strcat(tmp, *str);
			ft_memmove(tmp + i + 1, tmp + i, ft_strlen(tmp + i + 1) + 1);
			tmp[i] = '\\';
			ft_memmove(tmp + i + 1, tmp + i, ft_strlen(tmp + i + 1) + 1);
			tmp[i] = '\'';
			i += 2;
			ft_memmove(tmp + i + 1, tmp + i, ft_strlen(tmp + i + 1) + 1);
			tmp[i++] = '\'';
			free(*str);
			*str = tmp;
		}
		i += 1;
		if (0 == (*str)[i])
			break ;
	}
}
