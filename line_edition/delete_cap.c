/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_cap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:36:55 by apetitje          #+#    #+#             */
/*   Updated: 2017/06/19 18:30:07 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	delete_backward(t_i_line *i_line)
{
	char	*t;

	t = NULL;
	if (i_line->cursor.x + i_line->cursor.y == 0)
		return ;
	if (i_line->cursor.x > 0)
	{
		i_line->cursor.x -= 1;
		tputs(tgetstr("le", NULL), 0, ft_putchar);
	}
	else if (i_line->cursor.y > 0)
		curs_end_line_one_up(i_line);
	ft_asprintf(&t, "%s ", i_line->tmp);
	print_and_restore_curs(t, i_line);
	i_line->input.len--;
	i_line->input.data[i_line->input.len] = '\0';
	free(t);
}

void	delete_forward(t_i_line *i_line)
{
	char	*t;

	t = NULL;
	if (i_line->tmp_len == 0)
		return ;
	if (i_line->tmp_len == 1)
	{
		print_and_restore_curs(" ", i_line);
		del_tmp(i_line);
	}
	else
	{
		i_line->tmp_len -= 1;
		t = i_line->tmp;
		ft_asprintf(&i_line->tmp, "%s ", t + 1);
		ft_memdel((void **)&t);
		print_and_restore_curs(i_line->tmp, i_line);
		i_line->tmp[i_line->tmp_len] = '\0';
	}
}
