/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:49:42 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 21:37:04 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static void		command_locales(size_t *i, t_token *tok_tab, t_command *command)
{
	size_t			j;
	size_t			old_i;

	old_i = *i;
	while (*i < command->tok_size && tok_tab[*i].type == TOKEN_VAR)
		++(*i);
	if (!(command->locales = malloc(sizeof(char *) * ((*i - old_i) + 1))))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	(command->locales)[*i - old_i] = NULL;
	j = 0;
	while (old_i < *i)
	{
		if (!((command->locales)[j] = ft_strdup(tok_tab[old_i].word)))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		++old_i;
		++j;
	}
	--(*i);
}

static void		command_arguments(size_t *i, t_token *tok_tab,
		t_command *command)
{
	char		**tmp;
	int			j;
	size_t		old_i;

	old_i = *i;
	while (*i < command->tok_size && (tok_tab[*i].type == TOKEN_STR
		|| tok_tab[*i].type == TOKEN_VAR || tok_tab[*i].type == TOKEN_NULL))
		++(*i);
	command->argc += *i - old_i;
	tmp = command->argv;
	if (!(command->argv = malloc(sizeof(char *) * (command->argc + 1))))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	(command->argv)[command->argc] = NULL;
	j = 0;
	while (j < command->argc - (int)(*i - old_i))
		((command->argv)[j] = tmp[j]) ? ++j : 0;
	while (old_i < *i)
	{
		if (!((command->argv)[j] = ft_strdup(tok_tab[old_i].word)))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		++old_i;
		++j;
	}
	--(*i);
	ft_memdel((void **)&tmp);
}

static int		command_heredoc(t_token *tok_tab, size_t end_com,
		t_command *command, size_t *i)
{
	if (*i + 1 >= end_com || (tok_tab[*i + 1].type != TOKEN_STR
				&& tok_tab[*i + 1].type != TOKEN_VAR
				&& tok_tab[*i + 1].type != TOKEN_NULL))
		return (1);
	if (command->heredoc)
		ft_memdel((void **)&command->heredoc);
	++(*i);
	if (!(command->heredoc = ft_strdup(tok_tab[*i].word)))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	tok_tab[*i].type = TOKEN_VOID;
	return (0);
}

static int		command_sub_process(t_command *command, t_token *tok_tab,
		size_t *i)
{
	if (tok_tab[*i].type == TOKEN_HEREDOC)
	{
		if (command_heredoc(tok_tab, command->tok_size, command, i))
			return (1);
		add_to_redir_list(NULL, &(command->redirs), 0, REDIR_HEREDOC);
	}
	else if (command->argc == 0 && command->tokens[*i].type == TOKEN_VAR)
		command_locales(i, tok_tab, command);
	else if (tok_tab[*i].type == TOKEN_STR || tok_tab[*i].type == TOKEN_VAR
			|| tok_tab[*i].type == TOKEN_NULL)
		command_arguments(i, tok_tab, command);
	else if (tok_tab[*i].type != TOKEN_VOID)
		return (error_and_return("syntax error"));
	return (0);
}

int				command_process(t_command *command)
{
	size_t		i;

	i = 0;
	expands(&command->tokens, &command->tok_size);
	command->is_bg = g_bg ? 1 : 0;
	while (i < command->tok_size)
	{
		if (command->tokens[i].type == TOKEN_REDIR_L
				|| (command->tokens[i].type == TOKEN_REDIR_R)
				|| command->tokens[i].type == TOKEN_DB_REDIR_R)
		{
			if (i + 1 >= command->tok_size
					|| (command->tokens[i + 1].type != TOKEN_STR
						&& command->tokens[i + 1].type != TOKEN_VAR
						&& command->tokens[i + 1].type != TOKEN_NULL))
				return (error_and_return("syntax error"));
			if (parse_redirs(&(command->redirs), command->tokens, i))
				return (1);
		}
		else if (command_sub_process(command, command->tokens, &i))
			return (1);
		++i;
	}
	return (0);
}
