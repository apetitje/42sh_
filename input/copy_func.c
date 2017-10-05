/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 12:15:33 by apetitje          #+#    #+#             */
/*   Updated: 2017/06/05 22:22:35 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void	copy_before(t_i_line *i_line)
{
	ft_memdel((void **)&g_clipboard);
	if (i_line->input.len)
		if (!(g_clipboard = ft_strdup(i_line->input.data)))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
}

void	copy_after(t_i_line *i_line)
{
	ft_memdel((void **)&g_clipboard);
	if (i_line->tmp_len)
		if (!(g_clipboard = ft_strdup(i_line->tmp)))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
}

void	paste_clipboard(t_i_line *i_line)
{
	if (g_clipboard)
	{
		print_and_progress_curs(g_clipboard, i_line);
		ft_fill_buff(&i_line->input, g_clipboard, ft_strlen(g_clipboard));
	}
	if (i_line->tmp)
		print_and_restore_curs(i_line->tmp, i_line);
}
