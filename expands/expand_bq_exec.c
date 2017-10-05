/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bq_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 14:04:24 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/04 12:19:51 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static int	do_bq_child(char *line)
{
	t_token *tok_tab;
	t_ast	*root;
	char	*com_line;
	int		pipe_fds[3];

	if (!line || !*line)
		exit(0);
	com_line = NULL;
	root = NULL;
	subsh_command_pipe(pipe_fds, line);
	while (get_next_line(pipe_fds[0], &com_line) > 0)
	{
		init_tok_tab(&tok_tab, g_token_tab_size);
		if (parse_line(&com_line, &tok_tab, &g_token_tab_size)
				|| check_grammar(tok_tab) || ast_construct(tok_tab, &root))
		{
			ft_dprintf(2, "42sh: command substitution: syntax error\n");
			subsh_close_and_exit(pipe_fds, 0);
		}
		if (ast_do_commands(root))
			subsh_close_and_exit(pipe_fds, 0);
		free_subsh_vars(&tok_tab, root, &com_line);
	}
	subsh_close_and_exit(pipe_fds, 1);
	return (0);
}

static int	do_bq(char *line)
{
	pid_t	process;
	char	bksub;
	int		stat;

	stat = 0;
	bksub = g_currjob->subsh;
	g_currjob->subsh = 3;
	if ((process = fork()) == -1)
		return ((ft_dprintf(2, "42sh: fork failed\n")) ? -1 : -1);
	if (process == 0)
	{
		tcsetpgrp(0, g_currjob->pgid = getpid());
		signal(SIGINT, SIG_DFL);
		return (do_bq_child(line));
	}
	else
	{
		setpgid(process, process);
		tcsetpgrp(0, process);
		if (bksub)
			waitpid(process, &stat, WUNTRACED);
		g_currjob->subsh = bksub;
		tcsetpgrp(0, (bksub && g_currjob->pgid) ? g_currjob->pgid : g_shellpid);
		return (return_exit_status(stat, 0, 0));
	}
}

static void	read_new_line(int fd, char **new_line)
{
	char	*tmp;
	char	buff[SIZE];
	int		ret;

	while (fd != -1 && (ret = read(fd, buff, SIZE - 1)) && ret != -1)
	{
		buff[ret] = '\0';
		tmp = *new_line;
		ft_asprintf(new_line, "%s%s", tmp, buff);
		ft_memdel((void **)&tmp);
	}
}

static void	end_redir_bq(int pipe_fds[2], char **line, int stdin_save,
		int stdout_save)
{
	close(pipe_fds[1]);
	dup2(stdout_save, STDOUT_FILENO);
	read_new_line(pipe_fds[0], line);
	close(pipe_fds[0]);
	dup2(stdin_save, STDIN_FILENO);
	close(stdin_save);
	close(stdout_save);
}

void		redir_command_bq(char *com_line, char **line)
{
	int		pipe_fds[2];
	int		stdin_save;
	int		stdout_save;

	pipe(pipe_fds);
	fcntl(pipe_fds[1], F_SETFL, O_NONBLOCK);
	stdin_save = dup(STDIN_FILENO);
	stdout_save = dup(STDOUT_FILENO);
	dup2(pipe_fds[1], STDOUT_FILENO);
	if (do_bq(com_line) != 0)
	{
		close(pipe_fds[1]);
		dup2(stdout_save, STDOUT_FILENO);
		close(pipe_fds[0]);
		dup2(stdin_save, STDIN_FILENO);
		close(stdin_save);
		close(stdout_save);
		return ;
	}
	end_redir_bq(pipe_fds, line, stdin_save, stdout_save);
}
