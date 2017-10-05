/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 15:23:57 by hanguelk          #+#    #+#             */
/*   Updated: 2017/10/04 18:19:08 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static char		*ret_status_str(char type)
{
	if (type == 1)
		return ("Running");
	else if (type == 2)
		return ("Stopped");
	else if (type == 3)
		return ("Done");
	else
		return ("Unknows");
}

static void		display_job(t_job *j, char type)
{
	t_process	*p;

	if (type == -1)
		ft_printf("[%d]%c  %s\t\t\t%s\n", j->index, j->current,
				ret_status_str(j->active), j->cmdline);
	else if (type == 1)
		ft_printf("%d\n", j->pgid);
	else if (type == 2)
	{
		p = j->first;
		ft_printf("[%d]%c\t%d %s\t\t\t%s\n", j->index, j->current,
				p->cpid, ret_status_str(j->active), p->cmd);
		p = p->next;
		while (p)
		{
			ft_printf("\t%d\t\t\t\t%s\n", p->cpid, p->cmd);
			p = p->next;
		}
	}
}

static	void	list_jobs(int current_id, int specific, char type)
{
	char	flag;
	t_job	*j;

	j = g_jobs;
	flag = 0;
	while (j)
	{
		update_current_bt(j, current_id);
		if (j->index != current_id && specific == -1)
			display_job(j, type);
		else if (j->index == specific && current_id != specific && (flag = 1))
			display_job(j, type);
		j = j->next;
	}
	if (!flag && specific != -1)
		ft_printf("42sh: jobs: %d: no such job\n", specific);
}

static int		jobs_main(t_command *cmd, int i, int j, char type)
{
	while (cmd->argc > 1 && cmd->argc > i && (j = 1))
	{
		if (cmd->argv[i][0] == '-')
		{
			while (cmd->argv[i][j])
			{
				if (cmd->argv[i][j] == 'p')
					type = 1;
				else if (cmd->argv[i][j] == 'l')
					type = 2;
				else
					return (jobs_usage(cmd->argv[i][j]));
				j++;
			}
		}
		else
			break ;
		i++;
	}
	if (i != cmd->argc)
		while (i < cmd->argc)
			list_jobs(g_currjob->index, ft_atoi(cmd->argv[i++]), type);
	else
		list_jobs(g_currjob->index, -1, type);
	return (0);
}

int				ft_jobs(t_bt_args ar)
{
	int		i;
	int		j;
	int		bkfd[3];
	int		res;
	char	type;

	i = 1;
	j = 0;
	type = -1;
	res = 0;
	make_stdfd_bk((int*)bkfd);
	if (do_redirect(ar.cmd))
	{
		restore_stdfd((int*)bkfd);
		return (1);
	}
	res = jobs_main(ar.cmd, i, j, type);
	g_currjob->active = 3;
	restore_stdfd((int*)bkfd);
	return (res);
}
