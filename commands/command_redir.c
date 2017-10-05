/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 17:49:14 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 22:03:25 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		close_redirs(t_list *red)
{
	while (red)
	{
		if (((t_redir *)red->data)->redirs[2] != -1
				&& ((t_redir *)red->data)->redirs[2] != 1
				&& ((t_redir *)red->data)->redirs[2] != 0
				&& ((t_redir *)red->data)->redirs[2] != 2)
			close(((t_redir *)red->data)->redirs[2]);
		red = red->next;
	}
}

int			do_heredoc(t_command *command)
{
	int		pipe_fds[2];
	int		stdin_save;
	int		stdout_save;

	if (!command->heredoc)
		return (0);
	pipe(pipe_fds);
	stdin_save = dup(STDIN_FILENO);
	stdout_save = dup(STDOUT_FILENO);
	dup2(pipe_fds[1], STDOUT_FILENO);
	write(pipe_fds[1], command->heredoc, ft_strlen(command->heredoc));
	close(pipe_fds[1]);
	dup2(stdout_save, STDOUT_FILENO);
	dup2(pipe_fds[0], STDIN_FILENO);
	return (0);
}

static void	do_dups(t_list *red)
{
	dup2(((t_redir *)red->data)->redirs[2], 1);
	dup2(((t_redir *)red->data)->redirs[2], 2);
}

int			do_redirect(t_command *command)
{
	t_list		*red;
	const char	*error = "42sh: redirection error: no such file or directory";
	int			*red_infos;

	red = command->redirs;
	while (red)
	{
		red_infos = ((t_redir *)red->data)->redirs;
		if (red_infos[2] == -1 && red_infos[1] != REDIR_CLOSE)
			return (ft_dprintf(2, "%s\n", error));
		if (red_infos[1] == REDIR_HEREDOC)
			do_heredoc(command);
		else if (red_infos[1] == REDIR_CLOSE)
			close(red_infos[0]);
		else if (red_infos[1] == REDIR_TO || red_infos[1] == REDIR_APPEND)
			dup2(red_infos[2], red_infos[0]);
		else if (red_infos[1] == REDIR_TO_DUO
				|| red_infos[1] == REDIR_APPEND_DUO)
			do_dups(red);
		else
			dup2(red_infos[2], red_infos[0]);
		red = red->next;
	}
	return (0);
}
