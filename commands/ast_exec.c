/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 12:53:05 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/04 19:07:29 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int			ast_do_pipe(t_ast *root)
{
	int				stdin_save;

	stdin_save = -1;
	create_pipe_jobs();
	if (pipe_first_run(root, 3) || pipe_com(root, 3, &stdin_save))
	{
		g_currjob->pipeline = 0;
		return (1);
	}
	g_currjob->pipeline = 0;
	return (g_exit_status);
}

int			ast_sub_command(t_ast *root, int code)
{
	char	*line;

	if (root->type == AST_TOKEN
			&& ((t_token *)root->item)->type == TOKEN_SUBSH)
	{
		if (!(line = ft_strdup(((t_token *)root->item)->word)))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		if ((g_exit_status = open_subshell(&line, code)))
			return (1);
	}
	else if (root->type == AST_COMMAND)
	{
		create_inline_job(root->item);
		if (command_process(root->item))
			return (1);
		if (!((t_command *)root->item)->argc)
			return (0);
		g_exit_status = do_command(root->item, code);
	}
	return (0);
}

static int	ast_tokens(t_ast *root, t_tok_type type, int *exit)
{
	if (type == TOKEN_PIPE)
		return (ast_do_pipe(root));
	if (type == TOKEN_AND || type == TOKEN_OR)
	{
		if (and_or_com(root, exit))
			return (1);
		g_exit_status = *exit;
	}
	if (type == TOKEN_ESPER)
	{
		g_bg = 1;
		if (!root->left)
			return (error_and_return("command background syntax error"));
		if (background_com(root->left, 1))
			return (1);
		if (root->right)
			g_bg = 0;
		return (ast_do_commands(root->right));
	}
	return (0);
}

int			ast_do_commands(t_ast *root)
{
	int		exit;

	exit = 0;
	g_bg = (g_currjob->subsh && g_bg) ? 1 : 0;
	if (root)
	{
		update_last_exit_status(g_exit_status);
		if (root->type == AST_COMMAND && all_token_are_var(root->item))
			return (add_local_var(root->item));
		if (root->type == AST_TOKEN && (get_tok_type(root) == TOKEN_PIPE
				|| get_tok_type(root) == TOKEN_AND
				|| get_tok_type(root) == TOKEN_OR
				|| get_tok_type(root) == TOKEN_ESPER))
			return (ast_tokens(root, get_tok_type(root), &exit));
		if (root->left && ast_do_commands(root->left))
			return (1);
		if (ast_sub_command(root, 0))
			return (1);
		if (root->right && ast_do_commands(root->right))
			return (1);
	}
	return (0);
}
