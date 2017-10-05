/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curs_and_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 15:57:37 by apetitje          #+#    #+#             */
/*   Updated: 2017/06/05 22:23:01 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void		print_and_progress_curs(char *out, t_i_line *i_line)
{
	int		prompt;

	if (i_line->cursor.y)
		prompt = 0;
	else
		prompt = g_prompt_size;
	i_line->cursor.x += ft_printf("%s", out);
	if (i_line->cursor.x + prompt > i_line->ws.ws_col)
	{
		i_line->cursor.x -= i_line->ws.ws_col - prompt;
		i_line->cursor.y += 1;
		while (i_line->cursor.x > i_line->ws.ws_col)
		{
			i_line->cursor.x -= i_line->ws.ws_col;
			i_line->cursor.y += 1;
		}
	}
}

void		print_and_restore_curs(char *out, t_i_line *i_line)
{
	int		old_x;
	int		old_y;

	old_x = i_line->cursor.x;
	old_y = i_line->cursor.y;
	print_and_progress_curs(out, i_line);
	curs_beg_command(i_line);
	while (i_line->cursor.y < old_y)
	{
		tputs(tgetstr("do", NULL), 0, ft_putchar);
		++i_line->cursor.y;
	}
	while (i_line->cursor.x < old_x)
	{
		tputs(tgetstr("nd", NULL), 0, ft_putchar);
		++i_line->cursor.x;
	}
}

void		curs_erase_command(t_i_line *i_line)
{
	size_t	i;

	i = 0;
	curs_end_command(i_line);
	if (i_line->cursor.y + i_line->cursor.x == 0)
		return ;
	tputs(tgetstr("cr", NULL), 0, ft_putchar);
	if (i_line->cursor.y > 0)
	{
		while (--i_line->cursor.y >= 0)
		{
			tputs(tgetstr("ce", NULL), 0, ft_putchar);
			tputs(tgetstr("up", NULL), 0, ft_putchar);
		}
		i_line->cursor.x -= g_prompt_size;
		i_line->cursor.y = 0;
	}
	while (i < g_prompt_size)
	{
		tputs(tgetstr("nd", NULL), 0, ft_putchar);
		++i;
	}
	tputs(tgetstr("ce", NULL), 0, ft_putchar);
	i_line->cursor.x = 0;
}
