/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 17:26:02 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/05 02:53:10 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static void	close_fds_before_ret(int in_bk, int out_bk)
{
	dup2(in_bk, STDIN_FILENO);
	dup2(out_bk, STDOUT_FILENO);
	close(in_bk);
	close(out_bk);
}

static void	pipe_init(int pipe_fds[2], int *in_bk, int *out_bk, int *stdin_save)
{
	pipe(pipe_fds);
	fcntl(pipe_fds[0], F_SETFD, FD_CLOEXEC);
	fcntl(pipe_fds[1], F_SETFD, FD_CLOEXEC);
	*in_bk = dup(STDIN_FILENO);
	*out_bk = dup(STDOUT_FILENO);
	dup2(*stdin_save, STDIN_FILENO);
	close(*stdin_save);
}

int			do_pipe(t_ast *root, int *stdin_save,
		int code)
{
	int		pipe_fds[2];
	int		in_bk;
	int		out_bk;

	pipe_init(pipe_fds, &in_bk, &out_bk, stdin_save);
	if (code != 3)
		dup2(pipe_fds[1], STDOUT_FILENO);
	if (ast_sub_cmd_pipe(root, code))
	{
		close_fds_before_ret(in_bk, out_bk);
		return (error_and_return("syntax error"));
	}
	*stdin_save = pipe_fds[0];
	dup2(*stdin_save, STDIN_FILENO);
	close_fds_before_ret(in_bk, out_bk);
	close(pipe_fds[1]);
	if (!g_currjob->subsh && code == 3)
	{
		close(*stdin_save);
		check_pipe_ret();
		close(pipe_fds[0]);
	}
	else if (!g_currjob->subsh)
		set_foreground_job();
	return (0);
}

static int	pipe_sub_com(t_ast *root, int code, int *stdin_save)
{
	if (root->left->type == AST_COMMAND || (root->left->type == AST_TOKEN
				&& ((t_token *)root->left->item)->type == TOKEN_SUBSH))
		if (do_pipe(root->left, stdin_save, 1))
			return (1);
	if (root->right->type == AST_COMMAND || (root->right->type == AST_TOKEN
				&& ((t_token *)root->right->item)->type == TOKEN_SUBSH))
	{
		if (do_pipe(root->right, stdin_save, code))
			return (1);
	}
	else
		return (error_and_return("syntax error"));
	return (0);
}

int			pipe_com(t_ast *root, int code, int *stdin_save)
{
	if (root)
	{
		if (root->left && ((t_token *)root->left->item)->type == TOKEN_PIPE)
			if (pipe_com(root->left, 1, stdin_save))
				return (1);
		if (root->type == AST_TOKEN
				&& ((t_token *)root->item)->type == TOKEN_PIPE)
		{
			if (!root->left || !root->right)
				return (error_and_return("syntax error"));
			if (pipe_sub_com(root, code, stdin_save))
				return (1);
		}
		if (root->right)
			pipe_com(root->right, 1, stdin_save);
	}
	return (g_exit_status);
}
