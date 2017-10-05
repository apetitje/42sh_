/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capabilities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 19:11:45 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 14:07:39 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static int	interrupt_input(char buff[], t_i_line *i_line,
		t_list **hist)
{
	curs_end_command(i_line);
	free_tok_tab_content(g_tok_tab);
	unselect_hist(hist);
	ft_bzero(buff, 5);
	ft_printf("\n");
	tputs(tgetstr("cd", NULL), 0, ft_putchar);
	return (2);
}

static void	clear_scr(t_i_line *i_line)
{
	tputs(tgetstr("cl", NULL), 0, ft_putchar);
	(g_prompt_size >= 3) ? ft_dprintf(2, "$> ") : ft_dprintf(2, "> ");
	ft_printf("%s", i_line->input.data);
	if (i_line->tmp)
		print_and_restore_curs(i_line->tmp, i_line);
}

static void	special_keys(char buff[], t_i_line *i_line, t_list **hist)
{
	if (!ft_strncmp(buff, "\x1b\x1b\x5b\x43", 4)
			|| !ft_strncmp(buff, "\x1b\x1b\x5b\x44", 4))
		word_motion(i_line, buff[3]);
	else if (!ft_strncmp(buff, "\x1b\x1b\x5b\x42", 4)
			|| !ft_strncmp(buff, "\x1b\x1b\x5b\x41", 4))
		line_motion(i_line, buff[3]);
	else if (!ft_strncmp(buff, "\x1b\x5b\x48", 3))
		home_func(i_line);
	else if (!ft_strncmp(buff, "\x1b\x5b\x43", 3)
			|| !ft_strncmp(buff, "\x1b\x5b\x44", 3))
		arrow_func(buff[2], i_line);
	else if (!ft_strncmp(buff, "\x1b\x5b\x42", 3)
			|| !ft_strncmp(buff, "\x1b\x5b\x41", 3))
		hist_func(buff, i_line, hist);
	else if (!ft_strncmp(buff, "\x1b\x5b\x46", 3))
		end_func(i_line);
	else if (!ft_strncmp(buff, "\x1b\x5b\x33\x7e", 4))
		delete_forward(i_line);
}

static int	end_of_text(t_i_line *i_line)
{
	if (!i_line->input.len && !i_line->tmp_len && g_prompt_size == 3)
	{
		ft_free_i_line(i_line);
		term_conf(&g_infos, 2);
		free_all();
		ft_printf("exit\n");
		exit(g_exit_status);
	}
	else if (!i_line->input.len && !i_line->tmp_len)
		return (1);
	else
		delete_forward(i_line);
	return (0);
}

int			ft_termcap(char buff[], t_i_line *i_line,
		t_list **hist)
{
	if (buff[0] == 3)
		return (interrupt_input(buff, i_line, hist));
	else if (buff[0] == 12)
		clear_scr(i_line);
	else if (buff[0] == 21)
		copy_before(i_line);
	else if (buff[0] == 11)
		copy_after(i_line);
	else if (buff[0] == 25)
		paste_clipboard(i_line);
	else if (buff[0] == 18)
	{
		history_search(i_line, buff);
		return ((*buff == '\n') ? 3 : ft_termcap(buff, i_line, hist));
	}
	else if (!ft_strncmp(buff, "\x7f", 1))
		delete_backward(i_line);
	else if (buff[0] == 0x1b)
		special_keys(buff, i_line, hist);
	else if (!ft_strncmp(buff, "\t", 1))
		completion(i_line);
	else if (buff[0] == 4 && end_of_text(i_line))
		return (1);
	return (0);
}
