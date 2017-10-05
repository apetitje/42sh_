/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 15:34:45 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 21:06:27 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

char	*restore_and_return(t_i_line *i_line, int i)
{
	g_prompt_size = 3;
	if (i_line->input.len >= SIZE)
		ft_dprintf(2, "\n42sh: Command is too long\n");
	ft_free_i_line(i_line);
	if (term_conf(&g_infos, 2))
		exit_prog(EXIT_FAILURE, "Terminal configuration failure\n");
	if (i == -1)
		exit_prog(EXIT_FAILURE, "Read error\n");
	return (NULL);
}

char	*end_input(t_list **hist, t_i_line *i_line, int i, int ret)
{
	if (ret == 2)
		return (restore_and_return(i_line, i));
	else
		return (send_input(hist, i_line));
}

char	*receive_input(t_i_line *i_line, t_list **hist)
{
	char		buff[5];
	int			ret;
	int			i;

	if (getpid() == g_shellpid)
		tcsetpgrp(0, g_shellpid);
	ft_bzero(buff, 5);
	while ((i = read(0, buff, 1)) != -1 && i_line->input.len < SIZE)
	{
		if (ft_isprint(*buff))
			input_printable(i_line, buff);
		else if (*buff == '\n')
			return (send_input(hist, i_line));
		else
		{
			if (*buff == 033 && (i = read(0, buff + 1, 3)) == -1)
				break ;
			if ((ret = ft_termcap(buff, i_line, hist)) == 1)
				return (send_eof(i_line));
			else if (ret == 2 || ret == 3)
				return (end_input(hist, i_line, i, ret));
		}
		ft_bzero(buff, 5);
	}
	return (restore_and_return(i_line, i));
}

char	*read_line(t_list **hist)
{
	t_i_line	i_line;
	char		*line;

	ft_init_i_line(&i_line);
	(g_prompt_size >= 3) ? ft_dprintf(2, "$> ") : ft_dprintf(2, "> ");
	if (term_conf(&g_infos, 1))
		exit_prog(EXIT_FAILURE, "Terminal configuration failure\n");
	line = receive_input(&i_line, hist);
	return (line);
}
