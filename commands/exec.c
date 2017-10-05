/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:11:43 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/05 02:13:54 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static int		exec_father(int *stat, t_command *command, int code)
{
	if (!g_currjob->bg)
	{
		if (g_currjob->code == 3)
			wait_last(stat);
		else if (!g_currjob->code)
			waitpid(-g_currjob->pgid, stat, WUNTRACED);
	}
	close_redirs(command->redirs);
	return (return_exit_status(*stat, code, 0));
}

static int		exec_child(int stat, t_command *command, char **environ,
		char **ex)
{
	stat = execve(*ex, command->argv, environ);
	free_path(&environ);
	ft_memdel((void **)ex);
	exit(stat);
}

static void		prep_exec_father(t_command *command, pid_t process,
		char *ex, char **environ)
{
	if (!g_currjob->pgid)
	{
		g_currjob->pgid = process;
		if (g_currjob->bg && !g_currjob->subsh)
			ft_dprintf(2, "[%d] %d\n", g_currjob->index, g_currjob->pgid);
	}
	setpgid(process, g_currjob->pgid);
	if (!g_currjob->subsh || g_currjob->subsh == 2)
		set_foreground_job();
	process_add_to_job(g_currjob, process, command, NULL);
	free_path(&environ);
	ft_memdel((void **)&ex);
}

int				open_exec(t_command *command, char **environ,
		t_path path_struc, int code)
{
	pid_t	process;
	int		stat;
	char	*ex;
	int		is_path;

	is_path = 0;
	stat = build_ex(command, &ex, path_struc, &is_path);
	if ((process = fork()) != 0)
	{
		prep_exec_father(command, process, ex, environ);
		if (process == -1)
			return ((ft_dprintf(2, "42sh: fork failed\n")) ? -1 : -1);
		return (exec_father(&stat, command, code));
	}
	else
	{
		setpgid(0, g_currjob->pgid);
		if (!g_currjob->subsh || g_currjob->subsh == 2)
			set_foreground_job();
		if (!g_currjob->bg && g_currjob->subsh != 3)
			setdfl_jobsignal();
		if (do_redirect(command) || is_error(stat, command, is_path, ex) != 0)
			exit(1);
		return (exec_child(stat, command, environ, &ex));
	}
}
