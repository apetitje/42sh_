/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_bt_sub_current.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 16:33:13 by hanguelk          #+#    #+#             */
/*   Updated: 2017/10/01 19:22:12 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void			update_current_bt(t_job *j, int current_id)
{
	if (j->next && j->next->next && j->next->next->index == current_id)
		j->current = '-';
	else if (j->next && j->next->index == current_id)
		j->current = '+';
	else
		j->current = ' ';
}

void			loop_for_current(int current_id)
{
	t_job *j;

	j = g_jobs;
	while (j)
	{
		update_current_bt(j, current_id);
		j = j->next;
	}
}

void			resume_default(char g, t_job *tmp)
{
	t_job	*prev;

	while (tmp->next && tmp->next->index != g_currjob->index)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp->index != g_currjob->index)
		(g) ? resume_pid_fg(tmp) : resume_pid_bg(tmp);
	else
		ft_printf("42sh: %s: current: no such job\n", (g) ? "fg" : "bg");
}

int				jobs_usage(char c)
{
	ft_dprintf(2, "42sh: jobs: -%c: invalid option\n", c);
	ft_dprintf(2, "jobs: usage: jobs [-lp] [jobs id]\n");
	return (2);
}
