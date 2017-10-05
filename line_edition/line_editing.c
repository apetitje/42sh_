/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 19:01:40 by apetitje          #+#    #+#             */
/*   Updated: 2017/06/19 14:37:15 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void		home_func(t_i_line *i_line)
{
	char	*t;

	t = NULL;
	if (i_line->cursor.x + i_line->cursor.y == 0)
		return ;
	curs_beg_command(i_line);
	if (i_line->tmp_len)
	{
		t = i_line->tmp;
		i_line->tmp_len = 0;
	}
	i_line->tmp_len =
		ft_asprintf(&i_line->tmp, "%s%s", i_line->input.data, i_line->tmp);
	if (t)
		ft_memdel((void **)&t);
	ft_free_buff(&i_line->input);
}

void		end_func(t_i_line *i_line)
{
	if (i_line->tmp_len)
	{
		curs_end_command(i_line);
		ft_fill_buff(&i_line->input, i_line->tmp, i_line->tmp_len);
		del_tmp(i_line);
	}
}

static void	arrow_right(t_i_line *i_line, int prompt)
{
	char	*t;

	ft_fill_buff(&i_line->input, i_line->tmp, 1);
	if (i_line->tmp_len > 1)
	{
		t = i_line->tmp;
		i_line->tmp_len = ft_asprintf(&i_line->tmp, "%s", i_line->tmp + 1);
		ft_memdel((void **)&t);
	}
	else
		del_tmp(i_line);
	if (i_line->cursor.x + prompt + 1 >= i_line->ws.ws_col)
	{
		i_line->cursor.x = 0;
		i_line->cursor.y += 1;
		tputs(tgetstr("do", NULL), 0, ft_putchar);
	}
	else
	{
		i_line->cursor.x += 1;
		tputs(tgetstr("nd", NULL), 0, ft_putchar);
	}
}

void		arrow_func(char com, t_i_line *i_line)
{
	int		prompt;
	char	*t;

	prompt = (i_line->cursor.y) ? 0 : g_prompt_size;
	if (com == 0x43 && i_line->tmp_len)
		arrow_right(i_line, prompt);
	else if (com == 0x44 && i_line->cursor.x + i_line->cursor.y > 0)
	{
		if (i_line->cursor.x > 0)
		{
			i_line->cursor.x -= 1;
			tputs(tgetstr("le", NULL), 0, ft_putchar);
		}
		else if (i_line->cursor.y > 0)
			curs_end_line_one_up(i_line);
		t = (i_line->tmp_len) ? i_line->tmp : NULL;
		i_line->tmp_len = ft_asprintf(&i_line->tmp, "%s%s", i_line->input.data
				+ i_line->input.len - 1, i_line->tmp);
		ft_memdel((void**)&t);
		i_line->input.len -= 1;
		i_line->input.data[i_line->input.len] = '\0';
	}
}
