/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 11:02:30 by oyagci            #+#    #+#             */
/*   Updated: 2017/07/11 15:53:01 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void		unselect_hist(t_list **hist)
{
	t_list *p;

	p = *hist;
	while (p)
	{
		set_select(p, 0);
		p = p->next;
	}
}

void		stock_hist(t_i_line *i_line, t_list **hist)
{
	t_hist	*new;
	t_list	*add;
	int		fd;

	i_line->input.data = history_expansion(i_line->input.data);
	if ((i_line->input.len = ft_strlen(i_line->input.data)) <= 0)
		return ;
	add = NULL;
	if (!(new = malloc(sizeof(t_hist))))
		exit_prog(EXIT_FAILURE, "Malloc error.\n");
	new->select = 0;
	if (!(new->content = ft_strdup(i_line->input.data)))
		exit_prog(EXIT_FAILURE, "Malloc error.\n");
	if (!(add = ft_lstnew(new, sizeof(new))))
		exit_prog(EXIT_FAILURE, "Malloc error.\n");
	ft_lstadd(hist, add);
	if ((fd = open_hist(O_CREAT | O_WRONLY
					| O_APPEND, S_IRWXU)) != -1)
	{
		write(fd, i_line->input.data, i_line->input.len);
		write(fd, "\n", 1);
		close(fd);
	}
	unselect_hist(hist);
}

void		free_hist(t_list **hist)
{
	t_list	*p;
	t_list	*to_del;

	p = *hist;
	while (p)
	{
		to_del = p;
		set_hist(p, NULL);
		free(p->data);
		p = p->next;
		free(to_del);
	}
	*hist = NULL;
}

static void	hist_top(t_i_line *i_line, t_list **hist)
{
	t_list	*p;

	if (!(*hist))
		return ;
	tputs(tgetstr("cd", NULL), 0, ft_putchar);
	g_last_cmpl = 0;
	p = *hist;
	while (p && !get_select(p))
		p = p->next;
	p = (p) ? p : *hist;
	if (get_select(p) && !p->next)
		return ;
	if (get_select(p))
	{
		set_select(p, 0);
		p = p->next;
	}
	curs_erase_command(i_line);
	ft_free_i_line(i_line);
	print_and_progress_curs(get_hist(p), i_line);
	set_select(p, 1);
	ft_fill_buff(&i_line->input, get_hist(p), ft_strlen(get_hist(p)));
}

void		hist_func(char buff[], t_i_line *i_line, t_list **hist)
{
	t_list	*p;

	if (buff[2] == 0x42)
	{
		p = *hist;
		while (p && !get_select(p))
			p = p->next;
		if (!p)
			return ;
		tputs(tgetstr("cd", NULL), (g_last_cmpl = 0), ft_putchar);
		curs_erase_command(i_line);
		ft_free_i_line(i_line);
		if (get_select(p) && p->prev)
		{
			set_select(p, 0);
			p = p->prev;
			print_and_progress_curs(get_hist(p), i_line);
			ft_fill_buff(&i_line->input, get_hist(p), ft_strlen(get_hist(p)));
			set_select(p, 1);
		}
		else
			unselect_hist(hist);
	}
	else if (buff[2] == 0x41)
		hist_top(i_line, hist);
}
