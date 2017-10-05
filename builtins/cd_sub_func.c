/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_sub_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 18:30:51 by apetitje          #+#    #+#             */
/*   Updated: 2017/06/05 22:21:58 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	parse_dot(char **dir, int *i, int *j)
{
	++(*j);
	while ((*dir)[*i + *j] == '/')
		++(*j);
	ft_strcpy((*dir) + *i, (*dir) + *i + *j);
	--(*i);
}

int		parse_dot_dot(char **dir, int *i, int *j)
{
	char	*tmp;

	tmp = NULL;
	ft_asprintf(&tmp, "%.*s", *i, *dir);
	if (is_dir(tmp) != 1)
	{
		ft_memdel((void **)&tmp);
		return (1);
	}
	ft_memdel((void **)&tmp);
	while ((*dir)[*i + *j] == '.')
		++(*j);
	while ((*dir)[*i + *j] == '/')
		++(*j);
	tmp = *dir + *i + *j;
	--(*i);
	while (*i - 1 >= 0 && (*dir)[*i - 1] != '/')
		--(*i);
	(*i > 0) ? ft_strcpy(*dir + *i, tmp) : ft_strcpy(*dir, "/");
	--(*i);
	return (0);
}

int		convert_dir(char **dir)
{
	int		i;
	int		j;

	i = -1;
	while ((*dir)[++i])
		if ((*dir)[i] == '/' && (*dir)[i + 1] == '/')
		{
			ft_strcpy((*dir) + i, (*dir) + i + 1);
			--i;
		}
	i = -1;
	while ((*dir)[++i])
	{
		j = 0;
		if ((*dir)[i] == '.' && (!(*dir)[i + 1] || (*dir)[i + 1] == '/')
				&& i > 0 && (*dir)[i - 1] == '/')
			parse_dot(dir, &i, &j);
		else if ((*dir)[i] == '.' && (*dir)[i + 1] == '.'
				&& (*dir)[i + 2] != '.' && (i > 0 && (*dir)[i - 1] == '/'))
			if (parse_dot_dot(dir, &i, &j))
				return (1);
	}
	return (0);
}
