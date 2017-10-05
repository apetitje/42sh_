/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_read_readline2_sub.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 12:39:41 by oyagci            #+#    #+#             */
/*   Updated: 2017/10/02 15:03:06 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static int	conf_save(t_infos *infos, int fd_in)
{
	if (tcgetattr(fd_in, &infos->term) == -1)
		return (1);
	infos->old_conf = infos->term;
	infos->term.c_lflag &= ~(ICANON | ECHO | ISIG);
	infos->term.c_cc[VMIN] = 1;
	infos->term.c_cc[VTIME] = 0;
	return (0);
}

void		input_printable_read(t_i_line *i_line, char buff[], t_read_opt *opt)
{
	int		prompt;

	if (opt->silent)
	{
		ft_fill_buff(&i_line->input, buff, 1);
		return ;
	}
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

int			term_conf_read(t_infos *infos, int code, int fd_in)
{
	char		*name;
	int			ret;

	if (code == 1)
	{
		name = getenv("TERM");
		if (name == NULL)
			name = "vt100";
		if ((ret = tgetent(NULL, name)) < 0)
			return (ft_dprintf(2, "Could not access the termcap database.\n"));
		if (ret == 0)
			return (ft_dprintf(2, "Terminal type %s is not defined.\n", name));
		if (conf_save(infos, fd_in))
			return (1);
	}
	else
		infos->term = infos->old_conf;
	ret = tcsetattr(fd_in, TCSADRAIN, &infos->term);
	if (ret == -1)
		return (1);
	return (0);
}
