/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_line_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 16:38:15 by apetitje          #+#    #+#             */
/*   Updated: 2017/06/05 22:22:37 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_init_i_line(t_i_line *i_line)
{
	i_line->input.data = i_line->input.data1;
	i_line->input.stocked = 0;
	ft_bzero(i_line->input.data1, SIZE);
	i_line->input.len = 0;
	i_line->cursor.x = 0;
	i_line->cursor.y = 0;
	i_line->tmp_len = 0;
	ioctl(0, TIOCGWINSZ, &i_line->ws);
	i_line->tmp = NULL;
}

void	ft_free_buff(t_buff *buff)
{
	if (buff->stocked)
	{
		free(buff->data);
		buff->data = buff->data1;
	}
	ft_bzero(buff->data1, SIZE);
	buff->stocked = 0;
	buff->len = 0;
}

void	ft_free_i_line(t_i_line *i_line)
{
	ft_free_buff(&i_line->input);
	i_line->cursor.x = 0;
	i_line->cursor.y = 0;
	i_line->tmp_len = 0;
	if (i_line->tmp)
		ft_memdel((void **)&i_line->tmp);
}

void	del_tmp(t_i_line *i_line)
{
	if (i_line->tmp_len)
	{
		ft_memdel((void **)&i_line->tmp);
		i_line->tmp_len = 0;
	}
}

void	ft_fill_buff(t_buff *buff, const char *src, int len)
{
	if (len > 0 && src && *src && (buff->len + len + 1 <= SIZE))
	{
		ft_memcpy(buff->data + buff->len, src, len);
		buff->data[buff->len + len] = '\0';
	}
	else if (len > 0 && src && *src)
	{
		if (buff->stocked)
		{
			if (!(buff->data = ft_realloc(buff->data, 1 + len + buff->len,
							buff->len)))
				exit_prog(EXIT_FAILURE, "Malloc error.\n");
		}
		else
		{
			if (!(buff->data = ft_memalloc(sizeof(char)
							* (buff->len + len + 1))))
				exit_prog(EXIT_FAILURE, "Malloc error.\n");
			buff->data = ft_memcpy(buff->data, buff->data1, buff->len);
		}
		ft_memcpy(buff->data + buff->len, src, len);
		buff->data[buff->len + len] = '\0';
		buff->stocked = 1;
	}
	buff->len += len;
}
