/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 18:49:23 by hanguelk          #+#    #+#             */
/*   Updated: 2017/10/05 03:11:28 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void	update_process_stat(t_job *task, char stopped, pid_t pid)
{
	t_process	*p;

	p = task->first;
	while (p)
	{
		if (pid && pid == p->cpid)
			p->pstat = stopped;
		else if (pid == 0)
			p->pstat = stopped;
		p = p->next;
	}
}

t_job	*get_job_by_pgid(pid_t pgid)
{
	t_job		*jlst;
	t_process	*p;

	jlst = g_jobs;
	while (jlst)
	{
		if (jlst->pgid == pgid)
			return (jlst);
		else
		{
			p = jlst->first;
			while (p)
			{
				if (p->cpid == pgid)
					return (jlst);
				p = p->next;
			}
		}
		jlst = jlst->next;
	}
	return (NULL);
}

void	wait_nonblock(void)
{
	pid_t	pgid;
	int		i;
	int		stat;

	i = 0;
	while (i < 2048 &&
			(pgid = waitpid(WAIT_ANY, &stat, WNOHANG | WUNTRACED)) > 0)
	{
		if (pgid > 0)
		{
			update_current();
			if ((g_currjob = get_job_by_pgid(pgid)))
			{
				if (g_currjob->bg && is_last_proc(g_currjob, pgid))
					g_currjob->bg = 2;
				if (g_currjob->subsh == -1)
					return_exit_status(stat, 0, 0);
				else
					return_exit_status(stat, 0, pgid);
			}
		}
		i++;
	}
}

void	update_current(void)
{
	t_job	*j;

	j = g_jobs;
	while (j)
	{
		if (j->next && !j->next->next)
			j->current = '-';
		else if (!j->next)
			j->current = '+';
		else
			j->current = ' ';
		j = j->next;
	}
}

void	update_jobs_stat(void)
{
	t_job	*j;
	char	flag;

	j = g_jobs;
	while (j)
	{
		flag = 0;
		if (is_completed(j))
		{
			del_job(j);
			j = g_jobs;
			flag = 1;
		}
		else if (j && is_stopped(j))
			j->active = 2;
		else if (j)
			j->active = 1;
		j = (flag) ? j : j->next;
	}
	update_current();
}
