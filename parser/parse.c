/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 18:44:41 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/04 17:08:47 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	build_pipe(t_token *line, int begin, t_ast **root, int left_size)
{
	int			end_com;

	end_com = left_size;
	if (end_com < begin)
		return (1);
	while (left_size >= begin && line[left_size].type != TOKEN_PIPE)
		--left_size;
	if (left_size >= begin && line[left_size].type == TOKEN_PIPE)
	{
		if (!(*root = ast_create_node(line + left_size, AST_TOKEN)))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		++left_size;
		if (end_com >= left_size)
			if (command_tree(line, left_size, &((*root)->right), end_com))
				return (1);
		if (build_pipe(line, begin, &((*root)->left), left_size - 2))
			return (1);
	}
	else
	{
		++left_size;
		if (command_tree(line, left_size, root, end_com))
			return (1);
	}
	return (0);
}

static int	build_and_or(t_token *line, int begin, t_ast **root, int left_size)
{
	int			end_com;

	end_com = left_size;
	if (end_com < begin)
		return (1);
	while (left_size >= begin && line[left_size].type != TOKEN_OR
			&& line[left_size].type != TOKEN_AND)
		--left_size;
	if (left_size >= begin && (line[left_size].type == TOKEN_OR
				|| line[left_size].type == TOKEN_AND))
	{
		if (!(*root = ast_create_node(line + left_size, AST_TOKEN)))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		++left_size;
		if (end_com >= left_size)
			if (build_pipe(line, left_size, &((*root)->right), end_com))
				return (1);
		if (build_and_or(line, begin, &((*root)->left), left_size - 2))
			return (1);
	}
	else if (build_pipe(line, ++left_size, root, end_com))
		return (1);
	return (0);
}

static int	build_node(t_token *line, t_ast *root, int left_size, int end_com)
{
	if (!(root->left = ast_create_node(line + left_size, AST_TOKEN)))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	++left_size;
	if (end_com >= left_size)
		if (build_and_or(line, left_size, &(root->left->right), end_com))
			return (1);
	if (do_left(line, root->left, left_size - 1))
		return (1);
	return (0);
}

int			do_left(t_token *line, t_ast *root, int left_size)
{
	int		end_com;

	--left_size;
	end_com = left_size;
	if (end_com < 0)
		return (1);
	while (left_size >= 0 && line[left_size].type != TOKEN_SEMI
			&& line[left_size].type != TOKEN_ESPER)
		--left_size;
	if (left_size >= 0 && (line[left_size].type == TOKEN_SEMI
				|| line[left_size].type == TOKEN_ESPER))
	{
		if (build_node(line, root, left_size, end_com))
			return (1);
	}
	else
	{
		left_size = (left_size < 0) ? 0 : left_size;
		if (build_and_or(line, left_size, &(root->left), end_com))
			return (1);
	}
	return (0);
}

int			ast_construct(t_token *line, t_ast **root)
{
	int			left_size;

	left_size = 0;
	while (line[left_size].type != TOKEN_EOF)
		left_size++;
	if (!(*root = ast_create_node(line + left_size, AST_TOKEN)))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	if (left_size)
		if (do_left(line, *root, left_size))
			return (error_and_return("syntax error"));
	return (0);
}
