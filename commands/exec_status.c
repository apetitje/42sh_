/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 19:26:34 by hanguelk          #+#    #+#             */
/*   Updated: 2017/10/04 19:08:59 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void	if_stopped(pid_t pid)
{
	if (!g_currjob->notified && (g_currjob->notified = 1) &&
			(getpid() == g_shellpid))
		ft_printf("\n[%d]%c  %s\t\t\t%s\n", g_currjob->index,\
				g_currjob->current, "Stopped", g_currjob->cmdline);
	update_process_stat(g_currjob, 2, pid);
}

int		if_signaled(int stat, pid_t pid)
{
	int	sig;

	sig = WTERMSIG(stat);
	if (sig == SIGSEGV)
		ft_dprintf(2, "[%d]\t%d Segmentation Fault %s\n", g_currjob->index,\
				g_currjob->pgid, g_currjob->cmdline);
	else
		write(2, "\n", 1);
	update_process_stat(g_currjob, 3, pid);
	return (WTERMSIG(stat));
}

int		is_error(int ret, t_command *command, int is_path, char *ex)
{
	if (ret == -2)
		ft_dprintf(2, "42sh: %s: Permission denied\n", command->argv[0]);
	else if (ret == -3)
		ft_dprintf(2, "42sh: %s: No such file or directory\n",
				command->argv[0]);
	else if (is_path && is_exec(ex) == -1)
		ft_dprintf(2, "42sh: %s: is a directory\n", ex);
	else if (ret == -1)
		ft_dprintf(2, "42sh: %s: command not found\n", command->argv[0]);
	return (ret);
}

int		return_exit_status(int stat, int code, pid_t pid)
{
	if (stat < 0)
		return (stat);
	else if (WIFSTOPPED(stat))
		if_stopped(pid);
	else if (WIFSIGNALED(stat))
		stat = if_signaled(stat, pid);
	else if (WIFEXITED(stat))
	{
		if (code == 3 && g_currjob->bg)
			g_currjob->subsh = -1;
		if (g_currjob->bg == 2 && !g_currjob->notified &&
				(g_currjob->notified = 1))
			ft_printf("[%d]%c  Done\t\t\t%s\n", g_currjob->index,\
					g_currjob->current, g_currjob->cmdline);
		if (g_currjob->bg != 1)
			update_process_stat(g_currjob, 3, pid);
		stat = WEXITSTATUS(stat);
	}
	else
		update_process_stat(g_currjob, 1, pid);
	if (g_currjob->bg)
		tcsetpgrp(0, g_shellpid);
	return (stat);
}

void	wait_last(int *stat)
{
	t_process	*p;

	p = g_currjob->first;
	while (p->next)
		p = p->next;
	waitpid(p->cpid, stat, WUNTRACED);
}
