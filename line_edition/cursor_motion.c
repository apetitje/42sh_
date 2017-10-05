/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 14:06:43 by apetitje          #+#    #+#             */
/*   Updated: 2017/06/19 15:55:38 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static void		curs_end_line(t_i_line *i_line)
{
	while (i_line->cursor.x < i_line->ws.ws_col)
	{
		tputs(tgetstr("nd", NULL), 0, ft_putchar);
		i_line->cursor.x++;
	}
	if (i_line->cursor.y == 0)
		i_line->cursor.x -= g_prompt_size + 1;
	else
		i_line->cursor.x -= 1;
}

void			curs_beg_command(t_i_line *i_line)
{
	size_t		i;

	i = 0;
	if (i_line->cursor.x + i_line->cursor.y == 0)
		return ;
	if (i_line->cursor.y > 0)
	{
		while (--i_line->cursor.y >= 0)
			tputs(tgetstr("up", NULL), 0, ft_putchar);
		i_line->cursor.x -= g_prompt_size;
		i_line->cursor.y = 0;
	}
	tputs(tgetstr("cr", NULL), 0, ft_putchar);
	while (i < g_prompt_size)
	{
		tputs(tgetstr("nd", NULL), 0, ft_putchar);
		++i;
	}
	i_line->cursor.x = 0;
}

void			curs_end_command(t_i_line *i_line)
{
	int tot;
	int prompt;

	if (i_line->tmp_len == 0)
		return ;
	curs_beg_command(i_line);
	prompt = g_prompt_size;
	tot = i_line->input.len + i_line->tmp_len;
	tputs(tgetstr("cr", NULL), 0, ft_putchar);
	i_line->cursor.x = 0;
	while (tot + prompt >= i_line->ws.ws_col)
	{
		tputs(tgetstr("do", NULL), 0, ft_putchar);
		tot -= i_line->ws.ws_col - prompt;
		i_line->cursor.y += 1;
		prompt = 0;
	}
	while (++i_line->cursor.x < tot + 1 + prompt)
		tputs(tgetstr("nd", NULL), 0, ft_putchar);
	i_line->cursor.x -= 1 + prompt;
}

void			curs_end_line_one_up(t_i_line *i_line)
{
	i_line->cursor.y -= 1;
	tputs(tgetstr("up", NULL), 0, ft_putchar);
	tputs(tgetstr("cr", NULL), 0, ft_putchar);
	curs_end_line(i_line);
}
