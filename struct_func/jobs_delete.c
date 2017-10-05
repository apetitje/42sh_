/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 18:43:34 by hanguelk          #+#    #+#             */
/*   Updated: 2017/06/27 18:46:25 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static void		del_process_list(t_process *p)
{
	t_process *bk;

	while (p)
	{
		bk = p->next;
		ft_memdel((void**)&(p->cmd));
		ft_memdel((void**)&p);
		p = bk;
	}
}

static void		del_job_struct(t_job *job)
{
	ft_memdel((void**)&job->cmdline);
	del_process_list(job->first);
	ft_memdel((void**)&job);
}

void			del_job(t_job *j)
{
	t_job	*gj;
	t_job	*bk;

	gj = g_jobs;
	if (gj->index == j->index)
	{
		bk = gj->next;
		del_job_struct(gj);
		g_jobs = bk;
		return ;
	}
	else
	{
		while (gj->index != j->index)
		{
			bk = gj;
			gj = gj->next;
		}
		j = gj->next;
		del_job_struct(gj);
		bk->next = j;
	}
}
