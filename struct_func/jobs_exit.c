/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 11:16:26 by hanguelk          #+#    #+#             */
/*   Updated: 2017/10/05 00:45:58 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static int		count_job(void)
{
	int		i;
	t_job	*j;

	i = 0;
	j = g_jobs;
	while (j && ++i)
		j = j->next;
	return (i - 1);
}

int				display_exit_jobs(void)
{
	int			nj;
	static int	exit;

	if (g_interactive)
	{
		nj = count_job();
		if (nj && !g_currjob->subsh)
		{
			ft_dprintf(2, "There are %d stopped job(s).\n", nj);
			exit = (exit) ? 0 : 1;
		}
		else
			exit = 0;
	}
	return (exit);
}

void			set_foreground_job(void)
{
	if (g_currjob->bg || g_currjob->pgid < 0)
		tcsetpgrp(0, g_shellpid);
	else
		tcsetpgrp(0, g_currjob->pgid);
}
