/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 42:04:34 by apetitje          #+#    #+#             */
/*   Updated: 2017/06/19 19:28:38 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static int	subsh_tree(t_token *tok_tab, int begin, t_ast **root)
{
	if (!(*root = ast_create_node(tok_tab + begin, AST_TOKEN)))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	return (0);
}

void		copy_tokens_in_command(t_command *command, int begin, int end_com,
		t_token *tok_tab)
{
	int		i;
	t_token	*tokens;
	size_t	j;

	j = command->tok_size;
	tokens = command->tokens;
	i = begin;
	while (i <= end_com)
	{
		if (!(tokens[j].word = ft_strdup(tok_tab[i].word)))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		tokens[j].size = tok_tab[i].size;
		tokens[j].type = tok_tab[i].type;
		++i;
		++j;
	}
	command->tok_size = j;
}

int			command_tree(t_token *tok_tab, int begin, t_ast **root,
		int end_com)
{
	t_command	*command;

	command = NULL;
	if (tok_tab[begin].type == TOKEN_SUBSH)
		return (subsh_tree(tok_tab, begin, root));
	if (end_com < begin)
		return (1);
	if (!(command = malloc(sizeof(t_command))))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	init_tok_tab(&command->tokens, g_token_tab_size);
	command->tok_size = 0;
	copy_tokens_in_command(command, begin, end_com, tok_tab);
	command->argc = 0;
	command->is_bg = 0;
	command->argv = NULL;
	command->redirs = NULL;
	command->heredoc = NULL;
	command->locales = NULL;
	if (!(*root = ast_create_node(command, AST_COMMAND)))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	return (0);
}
