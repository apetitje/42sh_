/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_read_readline2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 12:20:23 by oyagci            #+#    #+#             */
/*   Updated: 2017/10/03 15:37:53 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

char			*interrupt(char buff[], t_i_line *i_line, t_read_opt *opt)
{
	curs_end_command(i_line);
	free_tok_tab_content(g_tok_tab);
	ft_bzero(buff, 5);
	ft_printf("\n");
	tputs(tgetstr("cd", NULL), 0, ft_putchar);
	ft_free_i_line(i_line);
	if (term_conf_read(&g_infos, 2, opt->fd_in))
		exit_prog(EXIT_FAILURE, "Terminal configuration failure\n");
	g_prompt_size = 3;
	return (NULL);
}

char			*send_in(t_i_line *i_line, t_read_opt *opt)
{
	char	*input;

	input = NULL;
	!opt->silent ? ft_putendl("") : 0;
	g_last_cmpl = 0;
	tputs(tgetstr("cd", NULL), 0, ft_putchar);
	i_line->input.data[i_line->input.len] = '\0';
	ft_fill_buff(&i_line->input, i_line->tmp, i_line->tmp_len);
	if (!(input = ft_strdup(i_line->input.data)))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	ft_free_i_line(i_line);
	g_prompt_size = 3;
	if (term_conf_read(&g_infos, 2, opt->fd_in))
	{
		free(input);
		ft_dprintf(2, "Terminal configuration failure\n");
		return (NULL);
	}
	return (input);
}

static int		write_c(int c)
{
	write(STDOUT_FILENO, &c, sizeof(char));
	return (0);
}

char			*recv_input(t_i_line *i_line, t_read_opt *opt)
{
	char				buff[5];
	int					i;

	while ((i = read(opt->fd_in, buff, 1)) != -1 && i != 0)
	{
		if (*buff == opt->delim)
			break ;
		if (ft_isprint(*buff))
			input_printable_read(i_line, buff, opt);
		else if (*buff == '\n')
			return (send_in(i_line, opt));
		else if (buff[0] == 3)
			return (interrupt(buff, i_line, opt));
		else if (buff[0] == 127 && i_line->input.len > 0)
		{
			tputs(tgetstr("le", 0), 0, write_c);
			tputs(tgetstr("dc", 0), 0, write_c);
			i_line->input.len -= 1;
		}
		else if (buff[0] == 4)
			return (NULL);
		if ((opt->nb_char_active && i_line->input.len >= opt->nb_char))
			break ;
	}
	return (send_in(i_line, opt));
}

char			*readline2(t_read_opt *opt)
{
	t_i_line	i_line;
	char		*line;

	line = NULL;
	if (opt->timeout)
	{
		set_alrm();
		ft_alarm(opt->timeout);
	}
	if (isatty(opt->fd_in) && opt->use_readline)
		return (readline(opt->prompt));
	else if (isatty(opt->fd_in))
	{
		ft_init_i_line(&i_line);
		if (term_conf_read(&g_infos, 1, opt->fd_in))
			exit_prog(EXIT_FAILURE, "Terminal configuration failure\n");
		g_prompt_size = 0;
		line = recv_input(&i_line, opt);
	}
	else
		get_next_line(opt->fd_in, &line);
	ft_alarm(0);
	g_prompt_size = 3;
	return (line);
}
