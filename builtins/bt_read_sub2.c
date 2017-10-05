/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_read_sub2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 13:59:51 by oyagci            #+#    #+#             */
/*   Updated: 2017/10/05 15:01:32 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		readline2_wrapper(char **line, t_read_opt *opt)
{
	char	*s;

	*line = NULL;
	if (!(s = readline2(opt)))
		return (-1);
	*line = s;
	return (0);
}

char	*get_input_loop(int ign_bslash, char *prompt, t_read_opt *opt)
{
	char	*tmp;
	char	*s;
	int		ret;

	s = NULL;
	tmp = NULL;
	while (1)
	{
		if (prompt && !opt->silent)
			ft_dprintf(2, "%s", prompt);
		if ((ret = readline2_wrapper(&tmp, opt)) < 0)
			break ;
		s = ft_stradd(s, tmp);
		ft_strdel(&tmp);
		if (s && (!s[0] || (s[ft_strlen(s) - 1]) != '\\' || ign_bslash))
			break ;
		s && s[0] ? (s[ft_strlen(s) - 1] = 0) : 0;
	}
	if (ret == -1)
		ft_strdel(&s);
	return (s);
}

char	*get_input(t_read_opt *opt)
{
	char	*s;

	read_set_signals(opt);
	if (opt->use_readline && isatty(STDIN_FILENO))
		s = readline(opt->prompt);
	else
		s = get_input_loop(opt->ign_bslash, opt->prompt, opt);
	ft_alarm(0);
	return (s);
}
