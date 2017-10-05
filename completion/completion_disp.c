/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_disp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 16:02:34 by clabouri          #+#    #+#             */
/*   Updated: 2017/08/16 10:58:12 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static void	disp_restore(t_i_line *il, t_list *matches, int col, int max_size)
{
	int i;
	int j;

	if ((j = (il->tmp_len + il->input.len + 1 + g_prompt_size) /
			il->ws.ws_col - il->cursor.y))
		tputs(tgoto(tgetstr("DO", NULL), 0, j), 0, ft_putchar);
	j++;
	ft_putchar('\n');
	while (matches && (i = col))
	{
		while (i--)
		{
			ft_printf("%-*s", (max_size + 2) * (col > 1), matches->data);
			j += (col == 1) ? (matches->data_size / il->ws.ws_col) : 0;
			if (!(matches = matches->next))
				break ;
		}
		ft_putchar('\n');
		j++;
	}
	tputs(tgoto(tgetstr("UP", NULL), 0, j), 0, ft_putchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_putchar);
	tputs(tgoto(tgetstr("RI", NULL), 0, (g_prompt_size +
		ft_strlen(il->input.data)) % il->ws.ws_col), 0, ft_putchar);
	print_and_restore_curs(il->tmp, il);
}

static void	disp_fscreen(t_i_line *il, t_list *matches, int col, int max_size)
{
	int	i;

	il->cursor.x = 0;
	il->cursor.y = 0;
	ft_putchar('\n');
	tputs(tgoto(tgetstr("UP", NULL), 0, 1), 0, ft_putchar);
	tputs(tgetstr("cd", NULL), 0, ft_putchar);
	while (matches && (i = col))
	{
		while (i--)
		{
			ft_printf("%-*s", (max_size + 2) * (col > 1), matches->data);
			if (!(matches = matches->next))
				break ;
		}
		ft_putchar('\n');
	}
	(g_prompt_size == 3) ? ft_putstr("$> ") : ft_putstr("> ");
	print_and_progress_curs(il->input.data, il);
	print_and_restore_curs(il->tmp, il);
}

static int	get_size(t_list *matches, int which)
{
	int	ret;
	int	tmp;

	if (!which)
	{
		ret = 1;
		while (matches)
		{
			tmp = ft_strlen((char*)matches->data);
			ret = (tmp > ret) ? tmp : ret;
			matches = matches->next;
		}
		return (ret);
	}
	ret = 0;
	while (matches)
	{
		ret++;
		matches = matches->next;
	}
	return (ret);
}

static void	prompt_cmpl(t_i_line *il, t_list *matches, int col, int max_size)
{
	char	buff[2];
	int		len;

	len = get_size(matches, 1);
	print_and_restore_curs(il->tmp, il);
	ft_dprintf(2, "\nDisplay all %d possibilities? (y or n)", len);
	tputs(tgetstr("cd", NULL), 0, ft_putchar);
	if (read(0, buff, 1) == -1)
		exit_prog(EXIT_FAILURE, "Read error\n");
	if (*buff != 'y')
	{
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_putchar);
		tputs(tgetstr("cd", NULL), 0, ft_putchar);
		tputs(tgoto(tgetstr("UP", NULL), 0, 1), 0, ft_putchar);
		tputs(tgoto(tgetstr("RI", NULL), 0,
			g_prompt_size + ft_strlen(il->input.data)), 0, ft_putchar);
		return ;
	}
	disp_fscreen(il, matches, col, max_size);
}

void		cmpl_cols(t_i_line *il, t_list *matches)
{
	int		col;
	int		len;
	int		max_size;

	max_size = get_size(matches, 0);
	len = get_size(matches, 1);
	ioctl(0, TIOCGWINSZ, &il->ws);
	col = il->ws.ws_col / (max_size + 2);
	col = (col) ? col : 1;
	if (len / col + 2 >= il->ws.ws_row)
	{
		prompt_cmpl(il, matches, col, max_size);
		return ;
	}
	g_last_cmpl = len / col;
	disp_restore(il, matches, col, max_size);
}
