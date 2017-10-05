/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_jobs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 17:50:19 by hanguelk          #+#    #+#             */
/*   Updated: 2017/10/05 03:40:21 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void			compute_pipeline_cmd(t_command *cmd, int code)
{
	char	*t2;
	char	*t3;
	char	*t1;

	if (g_currjob->cmdline == NULL)
		g_currjob->cmdline = recompute_cmd(cmd);
	else
	{
		t3 = recompute_cmd(cmd);
		ft_asprintf(&t2, "%s %s", g_currjob->cmdline, t3);
		free(t3);
		free(g_currjob->cmdline);
		g_currjob->cmdline = t2;
	}
	if (code != 3)
	{
		ft_asprintf(&t1, "%s | ", g_currjob->cmdline);
		free(g_currjob->cmdline);
		g_currjob->cmdline = t1;
	}
}

void			create_pipe_jobs(void)
{
	char	subsh;
	char	ao;
	char	bgn;
	pid_t	bk;

	bgn = g_currjob->bgnot;
	subsh = g_currjob->subsh;
	ao = g_currjob->ao;
	bk = g_currjob->pgid;
	if (g_currjob->pgid != 0)
		g_currjob = job_add(&g_jobs, NULL);
	if (subsh)
		g_currjob->pgid = bk;
	ft_memdel((void**)&g_currjob->cmdline);
	g_currjob->subsh = subsh;
	g_currjob->ao = ao;
	g_currjob->bgnot = bgn;
	g_currjob->pipeline = 1;
}

void			check_pipe_ret(void)
{
	int stat;

	stat = -1;
	if (g_currjob->pgid != -1 && g_currjob->pgid != g_shellpid)
	{
		waitpid(-g_currjob->pgid, &stat, WUNTRACED);
		if (WIFSTOPPED(stat) || WIFSIGNALED(stat))
			return_exit_status(stat, 0, 0);
	}
}
