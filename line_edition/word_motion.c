/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_motion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 16:04:40 by apetitje          #+#    #+#             */
/*   Updated: 2017/06/07 14:52:37 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void		line_motion(t_i_line *i_line, char arrow)
{
	int		i;

	i = 0;
	if (arrow == '\x42')
	{
		if (i_line->tmp_len >= i_line->ws.ws_col)
		{
			while (i < i_line->ws.ws_col)
			{
				++i;
				arrow_func(0x43, i_line);
			}
		}
	}
	else
	{
		if (i_line->input.len >= i_line->ws.ws_col)
		{
			while (i < i_line->ws.ws_col)
			{
				++i;
				arrow_func(0x44, i_line);
			}
		}
	}
}

static void	motion_left(t_i_line *i_line)
{
	size_t		ind;

	ind = i_line->input.len;
	if (ind == 0)
		return ;
	if (i_line->input.data[ind - 1] == ' ')
		while (ind > 0 && i_line->input.data[ind - 1] == ' ')
		{
			arrow_func(0x44, i_line);
			ind--;
		}
	else
		while (ind > 0 && i_line->input.data[ind - 1] != ' ')
		{
			arrow_func(0x44, i_line);
			ind--;
		}
}

static void	motion_right(t_i_line *i_line)
{
	char	*tmp;
	size_t	len;
	size_t	ind;

	tmp = NULL;
	ind = i_line->input.len;
	ft_asprintf(&tmp, "%s%s", i_line->input.data, i_line->tmp);
	len = ft_strlen(tmp);
	if (tmp[ind] == ' ')
		while (ind < len && tmp[ind] == ' ')
		{
			arrow_func(0x43, i_line);
			ind++;
		}
	else
		while (ind < len && tmp[ind] != ' ')
		{
			arrow_func(0x43, i_line);
			ind++;
		}
	ft_memdel((void **)&tmp);
}

void		word_motion(t_i_line *i_line, char com)
{
	if (com == 0x44)
		motion_left(i_line);
	if (com == 0x43)
		motion_right(i_line);
}
