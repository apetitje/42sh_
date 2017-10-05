/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_read_get_nb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 13:56:23 by oyagci            #+#    #+#             */
/*   Updated: 2017/10/03 13:56:29 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		get_nb(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (-1);
		i += 1;
	}
	return (ft_atoi(s));
}

int		is_opt_c(char *s, char c)
{
	if (s && s[0] == '-')
	{
		if (s[ft_strlen(s) - 1] == c)
			return (1);
	}
	return (0);
}
