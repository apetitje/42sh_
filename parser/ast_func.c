/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 13:28:54 by apetitje          #+#    #+#             */
/*   Updated: 2017/09/28 20:09:42 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

t_ast		*ast_create_node(void *item, t_ast_type type)
{
	t_ast			*node;

	if (!(node = malloc(sizeof(t_ast))))
		exit_prog(EXIT_FAILURE, "Malloc error (ast_create_node)\n");
	node->item = item;
	node->left = 0;
	node->right = 0;
	node->type = type;
	return (node);
}

static void	free_redir_list(t_list *redir)
{
	t_list			*t;

	while (redir)
	{
		t = redir;
		ft_memdel((void **)&((t_redir *)redir->data)->word);
		free(redir->data);
		redir = redir->next;
		free(t);
	}
	redir = NULL;
}

void		free_ast(t_ast *root)
{
	t_ast			*tree;

	tree = root;
	if (tree != 0)
	{
		if (root->left != 0)
			free_ast(tree->left);
		if (root->right != 0)
			free_ast(tree->right);
		if (tree->type == AST_COMMAND)
		{
			free_path(&(((t_command *)tree->item)->argv));
			free_path(&(((t_command *)tree->item)->locales));
			free_redir_list(((t_command *)tree->item)->redirs);
			if (((t_command *)tree->item)->heredoc)
				free(((t_command *)tree->item)->heredoc);
			free_tok_tab(&((t_command *)tree->item)->tokens);
			free(tree->item);
		}
		free(tree);
		tree = NULL;
	}
}
