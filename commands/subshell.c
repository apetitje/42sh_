/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 17:07:10 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/05 03:31:40 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void		init_subsh(char **line, int pipe_fds[])
{
	if (!line || !*line)
	{
		ft_dprintf(2, "42sh: subshell: syntax error\n");
		exit(1);
	}
	prepare_job_subsh_child();
	subsh_command_pipe(pipe_fds, *line);
}

static int	subsh_child(char **line)
{
	t_token *tok_tab;
	t_ast	*root;
	char	*com_line;
	int		ret;
	int		pipe_fds[3];

	root = NULL;
	init_subsh(line, pipe_fds);
	while ((ret = get_next_line(pipe_fds[0], &com_line)) && ret != -1)
	{
		init_tok_tab(&tok_tab, g_token_tab_size);
		if (parse_line(&com_line, &tok_tab, &g_token_tab_size)
				|| check_grammar(tok_tab) || ast_construct(tok_tab, &root))
		{
			ft_dprintf(2, "42sh: subshell: syntax error\n");
			subsh_close_and_exit(pipe_fds, 0);
		}
		if (ast_do_commands(root))
			subsh_close_and_exit(pipe_fds, 0);
		free_subsh_vars(&tok_tab, root, &com_line);
	}
	if (g_exit_status != 4735)
		subsh_close_and_exit(pipe_fds, 1);
	return (g_exit_status);
}

static void	prepare_job_subsh(pid_t process, char *line)
{
	ft_memdel((void**)&g_currjob->cmdline);
	if (!(g_currjob->cmdline = ft_strdup(line)))
		exit_prog(EXIT_FAILURE, "Malloc error (prepare_job_subsh)\n");
	(g_bg && g_currjob->bgnot == 1) ?
		ft_dprintf(2, "[%d] %d\n", g_currjob->index, process) : 0;
	process_add_to_job(g_currjob, process, NULL, line);
	if (!g_currjob->subsh && !g_currjob->pgid)
		g_currjob->pgid = process;
	g_currjob->subsh = 1;
	g_currjob->active = 1;
	setpgid(process, g_currjob->pgid);
	set_foreground_job();
}

int			open_subshell(char **line, int code)
{
	pid_t	process;
	int		stat;

	stat = 0;
	init_subsh_jobs();
	if ((process = fork()) == -1)
		return ((ft_dprintf(2, "42sh: fork failed\n")) ? 1 : 1);
	if (process == 0)
		return (subsh_child(line));
	else
	{
		prepare_job_subsh(process, *line);
		if (!code && (!g_bg))
		{
			waitpid(-g_currjob->pgid, &stat, WUNTRACED);
			g_currjob->pgid = (stat != 4735) ? 0 : g_currjob->pgid;
		}
		else if (code == 3)
			wait_last(&stat);
		ft_memdel((void **)line);
		g_currjob->subsh = 0;
		return (return_exit_status(stat, code, 0));
	}
}
