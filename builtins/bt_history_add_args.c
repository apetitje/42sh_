/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_history_add_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:26:12 by oyagci            #+#    #+#             */
/*   Updated: 2017/09/27 10:17:18 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

char		*history_add_args_loop(char **args)
{
	int		i;
	char	*s;
	char	*tmp;

	if (NULL == (s = ft_strnew(0)))
		exit_prog(EXIT_FAILURE, "malloc error (history_add_args)");
	i = 0;
	while (args[i])
	{
		tmp = s;
		if (NULL == (s = ft_strjoin(s, args[i])))
			exit_prog(EXIT_FAILURE, "malloc error history_add_args");
		free(tmp);
		if (args[i + 1])
		{
			tmp = s;
			if (NULL == (s = ft_strjoin(s, " ")))
				exit_prog(EXIT_FAILURE, "malloc error history_add_args");
			free(tmp);
		}
		i += 1;
	}
	return (s);
}

int			history_add_args(t_hist_opt *opt)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = history_add_args_loop(opt->av);
	if (g_hist)
	{
		if (ft_strlen(tmp) > 0)
		{
			free(get_hist(g_hist));
			((t_hist *)g_hist->data)->content = tmp;
		}
		else
			free(tmp);
	}
	return (0);
}
