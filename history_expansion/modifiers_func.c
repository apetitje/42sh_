/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 13:41:41 by oyagci            #+#    #+#             */
/*   Updated: 2017/07/11 13:41:51 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			rm_trailing_pathname_component(char **event)
{
	char	*trailing;
	int		i;

	if (!(trailing = ft_strrchr(*event, '/')))
		return ;
	i = 0;
	*trailing = 0;
}

void			rm_all_leading_pathname_component(char **event)
{
	int		i;
	char	*s;

	s = *event;
	i = ft_strlen(*event) - 1;
	while (i && s[i] != '/')
		i -= 1;
	if (s[i] == '/')
		ft_memmove(s, s + i + 1, ft_strlen(s + i) + 1);
}

void			rm_suffix(char **event)
{
	char	*suffix;

	if (!(suffix = ft_strrchr(*event, '.')))
		return ;
	*suffix = 0;
}

void			rm_all_but_trailing_suffix(char **event)
{
	char	*suffix;

	if (!(suffix = ft_strchr(*event, '.')))
		return ;
	ft_memmove(*event, suffix, ft_strlen(suffix) + 1);
}
