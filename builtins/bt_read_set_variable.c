/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_read_set_variable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 12:06:41 by oyagci            #+#    #+#             */
/*   Updated: 2017/10/03 14:54:36 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int		is_valid_identifier(char *name)
{
	int	i;

	if (ft_isdigit(*name))
		return (0);
	i = 0;
	while (name && name[i])
	{
		if (!(ft_isalnum(name[i]) || (name[i] == '_')))
			return (0);
		i += 1;
	}
	return (1);
}

int		set_variable(char *name, char *value)
{
	if (is_valid_identifier(name))
	{
		if (value && !g_currjob->pipeline)
			add_to_env(name, value, &g_locales);
		else if (!g_currjob->pipeline)
			add_to_env(name, "", &g_exported);
		return (0);
	}
	else
	{
		ft_dprintf(2, "Not a valid identifier: %s\n", name);
		return (1);
	}
}
