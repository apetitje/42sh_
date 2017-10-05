/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_com.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 22:11:55 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/05 03:38:20 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static t_job	*init_new_job(char subsh, t_command *arg)
{
	t_job	*j;
	char	*x;
	char	code;
	pid_t	bk;

	code = g_currjob->code;
	bk = g_currjob->pgid;
	x = recompute_cmd(arg);
	j = job_add(&g_jobs, x);
	j->ao = g_currjob->ao;
	free(x);
	g_currjob = j;
	g_currjob->pgid = (subsh) ? bk : 0;
	g_currjob->code = code;
	return (j);
}

void			create_inline_job(t_command *args)
{
	char	subsh;

	subsh = g_currjob->subsh;
	if (g_currjob->pgid == 0 || ((g_currjob->ao) && !subsh))
	{
		if (!g_currjob->ao)
		{
			free(g_currjob->cmdline);
			g_currjob->cmdline = recompute_cmd(args);
		}
		else if (g_currjob->ao)
			g_currjob = init_new_job(subsh, args);
		else
			g_currjob->pgid = (!g_currjob->bg && !subsh) ? 0 : g_currjob->pgid;
	}
	else
		g_currjob = init_new_job(subsh, args);
	g_currjob->subsh = subsh;
	g_currjob->bg = (g_bg) ? 1 : 0;
}

static int		and_or_com_right(t_ast *root, int *exit, char *line)
{
	if ((*exit && get_tok_type(root) == TOKEN_OR)
			|| (!*exit && get_tok_type(root) == TOKEN_AND))
	{
		if (root->right->type == AST_COMMAND)
		{
			create_inline_job(root->right->item);
			if (command_process(root->right->item))
				return (error_and_return("syntax error"));
			if (!((t_command *)root->right->item)->argc)
				return (0);
			*exit = do_command(root->right->item, 0);
		}
		else if (root->right->type == AST_TOKEN
				&& get_tok_type(root->right) == TOKEN_SUBSH)
			*exit = subshell_arithmetic(root, 1, line);
		else if (root->right->type == AST_TOKEN
				&& get_tok_type(root->right) == TOKEN_PIPE)
			*exit = ast_do_pipe(root->right);
	}
	g_exit_status = *exit;
	return (0);
}

static int		and_or_com_sub(t_ast *root, int *exit, char *line)
{
	if (!root->left || !root->right)
		return (error_and_return("syntax error"));
	if (root->left->type == AST_COMMAND)
	{
		create_inline_job(root->left->item);
		if (command_process(root->left->item))
			return (error_and_return("syntax error"));
		if (!((t_command *)root->left->item)->argc)
			return (0);
		*exit = do_command(root->left->item, 0);
	}
	else if (root->left->type == AST_TOKEN
			&& get_tok_type(root->left) == TOKEN_PIPE)
		*exit = ast_do_pipe(root->left);
	else if (root->left->type == AST_TOKEN
			&& get_tok_type(root->left) == TOKEN_SUBSH)
		*exit = subshell_arithmetic(root, 0, line);
	return (and_or_com_right(root, exit, line));
}

int				and_or_com(t_ast *root, int *exit)
{
	char	*line;

	line = NULL;
	g_currjob->ao = 1;
	if (root)
	{
		if (root->left && (get_tok_type(root->left) == TOKEN_OR
					|| get_tok_type(root->left) == TOKEN_AND))
			if (and_or_com(root->left, exit))
				return (1);
		if (root->type == AST_TOKEN
				&& (get_tok_type(root) == TOKEN_OR
					|| get_tok_type(root) == TOKEN_AND))
			if (and_or_com_sub(root, exit, line))
				return (1);
		if (root->right)
			if (and_or_com(root->right, exit))
				return (1);
	}
	return (0);
}
