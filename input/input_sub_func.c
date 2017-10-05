/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_sub_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 14:27:48 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 21:25:29 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void		ins_l(t_i_line *il)
{
	int	len;
	int	row;

	row = 0;
	len = (ft_strlen(il->input.data) + il->tmp_len + 1 + g_prompt_size);
	row = (il->ws.ws_col) ? len / il->ws.ws_col - il->cursor.y : row;
	len = (il->ws.ws_col) ? len % il->ws.ws_col : row;
	if (!len && g_last_cmpl)
	{
		tputs(tgoto(tgetstr("DO", NULL), 0, row), 0, ft_putchar);
		if (g_last_cmpl)
			tputs(tgoto(tgetstr("DO", NULL), 0, g_last_cmpl), 0, ft_putchar);
		ft_putchar('\n');
		tputs(tgoto(tgetstr("UP", NULL), 0, g_last_cmpl + 1), 0, ft_putchar);
		tputs(tgetstr("al", NULL), 0, ft_putchar);
		tputs(tgoto(tgetstr("UP", NULL), 0, row), 0, ft_putchar);
		tputs(tgoto(tgetstr("RI", NULL), 0, len), 0, ft_putchar);
	}
}

void		input_printable(t_i_line *i_line, char buff[])
{
	int		prompt;

	prompt = (i_line->cursor.y) ? 0 : g_prompt_size;
	ft_printf("%c", *buff);
	ins_l(i_line);
	if (i_line->cursor.x + prompt + 1 >= i_line->ws.ws_col)
	{
		i_line->cursor.y += 1;
		i_line->cursor.x = 0;
		tputs(tgetstr("do", NULL), 0, ft_putchar);
	}
	else
		i_line->cursor.x += 1;
	if (*buff != '\n' && i_line->tmp_len)
		print_and_restore_curs(i_line->tmp, i_line);
	ft_fill_buff(&i_line->input, buff, 1);
}

char		*send_input(t_list **hist, t_i_line *i_line)
{
	char	*input;

	input = NULL;
	ft_putendl("");
	g_last_cmpl = 0;
	tputs(tgetstr("cd", NULL), 0, ft_putchar);
	i_line->input.data[i_line->input.len] = '\0';
	ft_fill_buff(&i_line->input, i_line->tmp, i_line->tmp_len);
	(i_line->input.len && i_line->input.len < SIZE)
		? stock_hist(i_line, hist) : 0;
	if (i_line->input.len >= SIZE)
		ft_dprintf(2, "42sh: Command is too long\n");
	else if (!(input = ft_strdup(i_line->input.data)))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	ft_free_i_line(i_line);
	g_prompt_size = 3;
	if (term_conf(&g_infos, 2))
		exit_prog(EXIT_FAILURE, "Terminal configuration failure\n");
	return (input);
}

char		*send_eof(t_i_line *i_line)
{
	char *ret;

	ret = NULL;
	ft_free_i_line(i_line);
	if (term_conf(&g_infos, 2))
		exit_prog(EXIT_FAILURE, "Terminal configuration failure\n");
	g_prompt_size = 3;
	if (!(ret = ft_strdup("EOF")))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	return (ret);
}
