/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_sub_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:05:05 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/05 03:40:45 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void		prepare_job_subsh_child(void)
{
	if (g_currjob->pgid <= 0)
		g_currjob->pgid = getpid();
	g_currjob->subsh = 1;
	setpgid(getpid(), g_currjob->pgid);
	g_currjob->bgnot += (g_bg) ? 1 : 0;
	set_foreground_job();
	setdfl_jobsignal();
}

void		init_subsh_jobs(void)
{
	if ((g_currjob->bg = g_bg))
		g_currjob->bgnot += 1;
	if (g_currjob->pgid != -1)
		g_currjob->pgid = (g_currjob->ao && !g_currjob->subsh) ?
			0 : g_currjob->pgid;
	else
		g_currjob->pgid = g_shellpid;
}

void		subsh_close_and_exit(int pipe_fds[], int code)
{
	g_interactive = pipe_fds[2];
	g_subsh_fd = 0;
	close(pipe_fds[0]);
	if (!code)
		exit(1);
	exit(g_exit_status);
}

void		free_subsh_vars(t_token **tok_tab, t_ast *root, char **com_line)
{
	free_tok_tab(tok_tab);
	free_ast(root);
	ft_memdel((void **)com_line);
}

void		subsh_command_pipe(int pipe_fds[], char *line)
{
	pipe_fds[2] = g_interactive;
	g_interactive = 0;
	pipe(pipe_fds);
	write(pipe_fds[1], line, ft_strlen(line));
	close(pipe_fds[1]);
	g_subsh_fd = pipe_fds[0];
}
