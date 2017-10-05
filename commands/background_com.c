/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_com.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 16:05:51 by apetitje          #+#    #+#             */
/*   Updated: 2017/08/19 18:24:09 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static int	special_tokens(t_ast *root, t_tok_type type)
{
	int	exit;

	exit = 0;
	if (type == TOKEN_PIPE)
		return (ast_do_pipe(root));
	if (type == TOKEN_ESPER && (!root->left))
		return (error_and_return("command background syntax error"));
	if (type == TOKEN_AND || type == TOKEN_OR)
	{
		if (and_or_com(root, &exit))
			return (1);
		g_exit_status = 0;
	}
	if (type == TOKEN_SEMI)
	{
		g_bg = 1;
		if (ast_do_commands(root->left))
			return (1);
		g_bg = 1;
		if (root->right && ast_sub_command(root->right, 0))
			return (1);
	}
	return (0);
}

int			background_com(t_ast *root, int code)
{
	int		exit;

	exit = 0;
	if (root)
	{
		if (root->type == AST_TOKEN && (get_tok_type(root) == TOKEN_PIPE
					|| get_tok_type(root) == TOKEN_AND
					|| get_tok_type(root) == TOKEN_OR
					|| (get_tok_type(root) == TOKEN_ESPER && (!root->left))
					|| (get_tok_type(root) == TOKEN_SEMI && !code)))
			return (special_tokens(root, get_tok_type(root)));
		if (root->left && background_com(root->left, 0))
			return (1);
		if (ast_sub_command(root, 0))
			return (1);
		if (root->right && background_com(root->right, 0))
			return (1);
	}
	return (0);
}
