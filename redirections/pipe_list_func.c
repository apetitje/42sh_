/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_list_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 20:41:33 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/05 02:53:39 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int			ast_sub_cmd_pipe(t_ast *root, int code)
{
	char	*line;

	g_currjob->code = code;
	if (root->type == AST_TOKEN
			&& ((t_token *)root->item)->type == TOKEN_SUBSH)
	{
		if (!(line = ft_strdup(((t_token *)root->item)->word)))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		if ((g_exit_status = open_subshell(&line, code)))
			return ((g_exit_status == 4735 || g_exit_status == 0) ? 0 : 1);
	}
	else if (root->type == AST_COMMAND)
	{
		if (!((t_command *)root->item)->argc)
			return (0);
		g_currjob->bg = (((t_command *)root->item)->is_bg) ? 1 : 0;
		g_exit_status = do_command(root->item, code);
	}
	return (0);
}

static int	pipe_first_com(t_ast *root, int code)
{
	if (root->left->type == AST_COMMAND)
	{
		if (command_process(root->left->item))
			return (1);
		compute_pipeline_cmd((t_command *)root->left->item, code);
	}
	if (root->right->type == AST_COMMAND)
	{
		if (command_process(root->right->item))
			return (1);
		compute_pipeline_cmd((t_command *)root->right->item, code);
	}
	return (0);
}

int			pipe_first_run(t_ast *root, int code)
{
	if (root)
	{
		if (root->left && ((t_token *)root->left->item)->type == TOKEN_PIPE)
			if (pipe_first_run(root->left, 1))
				return (1);
		if (root->type == AST_TOKEN
				&& ((t_token *)root->item)->type == TOKEN_PIPE)
		{
			if (!root->left || !root->right)
				return (error_and_return("syntax error"));
			if (pipe_first_com(root, code))
				return (1);
		}
		if (root->right)
			pipe_first_run(root->right, 1);
	}
	return (0);
}
