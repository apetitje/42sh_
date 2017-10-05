/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_bt_sub_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 16:29:59 by hanguelk          #+#    #+#             */
/*   Updated: 2017/10/04 14:27:43 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void			resume_pid_fg(t_job *task)
{
	int		stat;
	t_job	*me;

	me = g_currjob;
	g_currjob = task;
	if (task->pgid == -1)
		stat = resume_if_shellpgid(g_currjob);
	else
	{
		kill(-task->pgid, SIGCONT);
		g_currjob->notified = 0;
		tcsetpgrp(0, task->pgid);
		if (g_currjob->code == 3)
			wait_last(&stat);
		else
			waitpid(-task->pgid, &stat, WUNTRACED);
		loop_for_current(me->index);
	}
	return_exit_status(stat, 0, 0);
	g_currjob = me;
}

void			resume_pid_bg(t_job *task)
{
	t_job	*me;

	me = g_currjob;
	g_currjob = task;
	kill(-task->pgid, SIGCONT);
	task->notified = 1;
	task->bg = 1;
	tcsetpgrp(0, g_shellpid);
	g_currjob = me;
}

static int		resume_jobs(t_command *args, char g)
{
	t_job		*tmp;
	int			id;

	tmp = g_jobs;
	if (args->argc == 1)
		resume_default(g, tmp);
	else if (args->argv[1])
	{
		id = ft_atoi(args->argv[1]);
		while (tmp)
		{
			if (tmp->index == id && tmp->index != g_currjob->index)
			{
				(g) ? resume_pid_fg(tmp) : resume_pid_bg(tmp);
				break ;
			}
			tmp = tmp->next;
		}
		if (tmp == NULL)
			ft_printf("42sh: %s: %d: no such job\n", (g) ? "fg" : "bg", id);
	}
	g_currjob->active = 3;
	return (0);
}

int				fg_jobs(t_bt_args ar)
{
	int	bkfd[3];
	int	res;

	make_stdfd_bk((int *)bkfd);
	if (do_redirect(ar.cmd))
	{
		restore_stdfd((int*)bkfd);
		return (1);
	}
	res = resume_jobs(ar.cmd, 1);
	restore_stdfd((int*)bkfd);
	return (res);
}

int				bg_jobs(t_bt_args ar)
{
	int bkfd[3];
	int res;

	make_stdfd_bk((int *)bkfd);
	if (do_redirect(ar.cmd))
	{
		restore_stdfd((int*)bkfd);
		return (1);
	}
	res = resume_jobs(ar.cmd, 0);
	restore_stdfd((int*)bkfd);
	return (res);
}
