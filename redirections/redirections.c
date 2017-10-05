/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 13:08:10 by apetitje          #+#    #+#             */
/*   Updated: 2017/09/29 16:29:40 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	find_first(t_token *line)
{
	int		first;

	first = -1;
	if (ft_isdigit((*line).word[0]))
		first = ft_atoi((*line).word);
	else if ((*line).type == TOKEN_REDIR_L)
		first = 0;
	else
		first = 1;
	if (first < 0)
		ft_dprintf(2, "42sh: file descriptor error\n");
	return (first);
}

static void	redir_stdin_stderr(t_token *line, t_list **redirs)
{
	if ((*line).type == TOKEN_REDIR_R)
	{
		if ((*line).word[2] == '&')
		{
			add_to_redir_list(line + 1, redirs, 1, REDIR_TO_FD);
			add_to_redir_list(line + 1, redirs, 2, REDIR_TO_FD);
		}
		else
			add_to_redir_list(line + 1, redirs, 1, REDIR_TO_DUO);
	}
	else if ((*line).word[2] == '&')
	{
		add_to_redir_list(line + 1, redirs, 1, REDIR_APPEND_FD);
		add_to_redir_list(line + 1, redirs, 2, REDIR_APPEND_FD);
	}
	else
		add_to_redir_list(line + 1, redirs, 1, REDIR_APPEND_DUO);
}

static void	find_redir_left_type(t_token *line, int j, t_list **redirs,
		int first)
{
	if ((*line).word[j] == '&')
		add_to_redir_list(line + 1, redirs, first, REDIR_FROM_FD);
	else if ((*line).word[j] == '>')
		add_to_redir_list(line + 1, redirs, first, REDIR_BOTH);
	else
		add_to_redir_list(line + 1, redirs, first, REDIR_FROM);
}

int			parse_redirs(t_list **redirs, t_token *line, int i)
{
	int		first;
	int		j;

	j = 0;
	if ((first = find_first(line + i)) < 0)
		return (1);
	if (line[i].word[0] == '&' && line[i].type != TOKEN_REDIR_L)
		redir_stdin_stderr(line + i, redirs);
	else
	{
		while (line[i].word[j] != '<' && line[i].word[j] != '>')
			++j;
		++j;
		if (line[i].type == TOKEN_REDIR_L)
			find_redir_left_type(line + i, j, redirs, first);
		else if (line[i].type == TOKEN_REDIR_R)
			add_to_redir_list(line + i + 1, redirs, first,
					(line[i].word[j] == '&') ? REDIR_TO_FD : REDIR_TO);
		else if (line[i].type == TOKEN_DB_REDIR_R)
			add_to_redir_list(line + i + 1, redirs, first,
					(line[i].word[j] == '&') ? REDIR_APPEND_FD : REDIR_APPEND);
	}
	return (0);
}
