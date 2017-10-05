/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 12:22:04 by apetitje          #+#    #+#             */
/*   Updated: 2017/07/11 15:52:17 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static void	search_advance(t_i_line *i_line, t_list *matches)
{
	t_list	*m;

	m = matches;
	while (m)
	{
		if (get_select(m) == 1)
		{
			set_select(m, 0);
			m = m->next;
			if (!m)
				m = matches;
			set_select(m, 1);
			ft_free_buff(&i_line->input);
			del_tmp(i_line);
			ft_fill_buff(&i_line->input, get_hist(m), ft_strlen(get_hist(m)));
			break ;
		}
		m = m->next;
	}
}

static void	history_search_init(t_i_line *i_line, char buff[],
		t_list **matches, char word[])
{
	end_func(i_line);
	*matches = NULL;
	ft_bzero(word, 2048);
	g_prompt_size = 0;
	ft_bzero(buff, 5);
	print_search_result(i_line, word);
}

static int	history_sub_search(t_i_line *i_line, t_list **matches,
		char buff[], char word[])
{
	if (*buff == 0x7f)
	{
		if (ft_strlen(word) > 0)
		{
			word[ft_strlen(word) - 1] = '\0';
			fill_search(word, i_line, matches);
		}
	}
	else
	{
		g_prompt_size = 3;
		if (*buff != 3)
		{
			erase_line(i_line);
			ft_printf("$> ");
			print_and_progress_curs(i_line->input.data, i_line);
		}
		if (*matches)
			free_hist(matches);
		return (1);
	}
	return (0);
}

void		history_search_is_print(char buff[], char word[],
		t_i_line *i_line, t_list **matches)
{
	if (ft_strlen(word) == 2047)
	{
		ft_dprintf(2, "\n42sh : command is too long\n");
		ft_bzero(word, 2048);
	}
	else
	{
		ft_strcat(word, buff);
		fill_search(word, i_line, matches);
	}
}

void		history_search(t_i_line *i_line, char buff[])
{
	t_list	*matches;
	char	word[2048];

	tputs(tgetstr("cd", NULL), 0, ft_putchar);
	g_last_cmpl = 0;
	history_search_init(i_line, buff, &matches, word);
	while ((read(0, buff, 4)) != -1)
	{
		if (ft_isprint(*buff))
			history_search_is_print(buff, word, i_line, &matches);
		else if (*buff == 18)
			search_advance(i_line, matches);
		else if (history_sub_search(i_line, &matches, buff, word))
			return ;
		ft_bzero(buff, 5);
		print_search_result(i_line, word);
	}
	if (matches)
		free_hist(&matches);
}
