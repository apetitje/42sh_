/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 13:44:04 by hanguelk          #+#    #+#             */
/*   Updated: 2017/10/05 03:17:54 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int		is_completed(t_job *task)
{
	t_process	*p;

	if (task->active == 3)
		return (1);
	p = task->first;
	while (p)
	{
		if (p->pstat != 3)
			return (0);
		p = p->next;
	}
	return (1);
}

int		is_stopped(t_job *task)
{
	t_process	*p;

	if (task->active == 2)
		return (1);
	p = task->first;
	while (p)
	{
		if (p->pstat != 2)
			return (0);
		p = p->next;
	}
	return (1);
}

int		is_last_proc(t_job *task, pid_t pid)
{
	t_process *p;

	p = task->first;
	while (p->next)
		p = p->next;
	return ((p->cpid == pid) ? 1 : 0);
}

void	ignore_jobsignal(void)
{
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
}

void	setdfl_jobsignal(void)
{
	signal(SIGTSTP, SIG_DFL);
	signal(SIGCONT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (!g_currjob->subsh)
	{
		signal(SIGTTOU, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
	}
}
