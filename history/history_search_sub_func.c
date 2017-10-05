/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search_sub_func.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:04:59 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 12:58:34 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void	erase_line(t_i_line *i_line)
{
	tputs(tgetstr("cr", NULL), 0, ft_putchar);
	tputs(tgetstr("ce", NULL), 0, ft_putchar);
	if (i_line->cursor.y > 0)
	{
		while (--i_line->cursor.y >= 0)
		{
			tputs(tgetstr("up", NULL), 0, ft_putchar);
			tputs(tgetstr("ce", NULL), 0, ft_putchar);
		}
		i_line->cursor.y = 0;
	}
	tputs(tgetstr("ce", NULL), 0, ft_putchar);
	i_line->cursor.x = 0;
}

void	print_search_result(t_i_line *i_line, char *word)
{
	erase_line(i_line);
	print_and_progress_curs("history search `", i_line);
	print_and_progress_curs(word, i_line);
	print_and_progress_curs("': ", i_line);
	print_and_progress_curs(i_line->input.data, i_line);
}

void	fill_search(char *word, t_i_line *i_line, t_list **matches)
{
	find_matches(word, matches);
	if (*matches)
	{
		ft_free_buff(&i_line->input);
		del_tmp(i_line);
		ft_fill_buff(&i_line->input, get_hist(*matches),
				ft_strlen(get_hist(*matches)));
	}
}

void	find_matches(char *word, t_list **matches)
{
	t_list	*h;
	t_hist	*new;
	t_list	*ele;

	(*matches) ? free_hist(matches) : 0;
	if (!*word)
		return ;
	h = g_hist;
	while (h)
	{
		if (ft_strstr(get_hist(h), word))
		{
			if (!(new = malloc(sizeof(t_hist))))
				exit_prog(EXIT_FAILURE, "Malloc error\n");
			new->select = (!*matches) ? 1 : 0;
			if (!(new->content = ft_strdup(get_hist(h))))
				exit_prog(EXIT_FAILURE, "Malloc error\n");
			if (!(ele = ft_lstnew(new, sizeof(new))))
				exit_prog(EXIT_FAILURE, "Malloc error\n");
			ft_lstaddback(matches, ele);
		}
		h = h->next;
	}
}
