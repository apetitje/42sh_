/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 11:56:34 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 21:42:24 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	is_numeric(const char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}

static void	open_redir_file(t_redir *r)
{
	char	*path;
	char	w_dir[MAXPATHLEN + 1];

	path = NULL;
	if (r->word[0] != '/')
	{
		getcwd(w_dir, MAXPATHLEN + 1);
		ft_asprintf(&path, "%s/%s", w_dir, r->word);
	}
	else if (!(path = ft_strdup(r->word)))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	ft_memdel((void **)&r->word);
	if (r->redirs[1] == REDIR_FROM)
		r->redirs[2] = open(path, O_RDONLY | O_NONBLOCK);
	else if (r->redirs[1] == REDIR_BOTH)
		r->redirs[2] = open(path, O_RDWR | O_NONBLOCK | O_CREAT, 0666);
	else if (r->redirs[1] == REDIR_TO || r->redirs[1] == REDIR_TO_DUO)
		r->redirs[2] = open(path, O_WRONLY | O_NONBLOCK | O_TRUNC
				| O_CREAT, 0666);
	else if (r->redirs[1] == REDIR_APPEND || r->redirs[1] == REDIR_APPEND_DUO)
		r->redirs[2] = open(path, O_WRONLY | O_APPEND | O_CREAT
				| O_NONBLOCK, 0666);
	ft_memdel((void **)&path);
}

static void	redir_file(t_list **redirs_list, t_redir *r, int type,
		t_token *line)
{
	t_list		*new;

	if (!(r->word = ft_strdup((*line).word)))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	r->redirs[1] = type;
	open_redir_file(r);
	if (!(new = ft_lstnew(r, sizeof(r))))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	ft_lstaddback(redirs_list, new);
	(*line).type = TOKEN_VOID;
}

static void	redir_fd(t_list **redirs_list, t_redir *r, int type, t_token *line)
{
	t_list		*new;

	new = NULL;
	(*line).type = TOKEN_VOID;
	if (!ft_strcmp((*line).word, "-"))
	{
		r->redirs[1] = REDIR_CLOSE;
		r->redirs[2] = -1;
	}
	else
	{
		r->redirs[1] = (type == REDIR_FROM_FD) ? REDIR_FROM : r->redirs[1];
		r->redirs[1] = (type == REDIR_TO_FD) ? REDIR_TO : r->redirs[1];
		r->redirs[1] = (type == REDIR_APPEND_FD) ? REDIR_APPEND : r->redirs[1];
		r->redirs[1] = (type == REDIR_BOTH_FD) ? REDIR_BOTH : r->redirs[1];
		if (!is_numeric((*line).word))
		{
			redir_file(redirs_list, r, r->redirs[1], line);
			return ;
		}
		r->redirs[2] = ft_atoi((*line).word);
	}
	if (!(new = ft_lstnew(r, sizeof(r))))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	ft_lstaddback(redirs_list, new);
}

void		add_to_redir_list(t_token *line, t_list **redirs_list,
		int first, int type)
{
	t_redir		*redir;
	t_list		*new;

	new = NULL;
	redir = NULL;
	if (!(redir = malloc(sizeof(t_redir))))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	redir->redirs[0] = first;
	redir->redirs[2] = 0;
	redir->word = NULL;
	if (type == REDIR_HEREDOC)
	{
		redir->redirs[1] = type;
		if (!(new = ft_lstnew(redir, sizeof(redir))))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		ft_lstaddback(redirs_list, new);
	}
	else if (type == REDIR_APPEND || type == REDIR_TO
			|| type == REDIR_FROM || type == REDIR_BOTH
			|| type == REDIR_TO_DUO || type == REDIR_APPEND_DUO)
		redir_file(redirs_list, redir, type, line);
	else
		redir_fd(redirs_list, redir, type, line);
}
