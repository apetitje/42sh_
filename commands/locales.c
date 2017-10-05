/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locales.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 20:33:49 by hanguelk          #+#    #+#             */
/*   Updated: 2017/09/25 16:05:29 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void			update_last_exit_status(int stat)
{
	char	*s;

	ft_asprintf(&s, "%d", stat);
	add_to_env("?", s, &g_locales);
	free(s);
}

static int		update_env_if_exist(char *nme, char *content)
{
	t_list *ev;

	ev = g_env;
	while (ev)
	{
		if (!ft_strcmp(get_var(ev), nme))
		{
			add_to_env(nme, content, &g_env);
			return (1);
		}
		ev = ev->next;
	}
	return (0);
}

static void		alloc_local_var(t_command *cmd, size_t i,
		char **content, char **var)
{
	size_t sze;

	sze = ft_strchr(cmd->tokens[i].word, '=') - cmd->tokens[i].word;
	if (!(*var = ft_strndup(cmd->tokens[i].word, sze)))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	if (cmd->tokens[i].size > sze + 1)
	{
		if (!(*content = ft_strdup(&(cmd->tokens[i].word[sze + 1]))))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
	}
	else
	{
		if (!(*content = ft_strdup("\0")))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
	}
}

int				add_local_var(t_command *cmd)
{
	char	*var;
	char	*content;
	size_t	i;

	i = 0;
	expands(&cmd->tokens, &cmd->tok_size);
	while (i < cmd->tok_size)
	{
		alloc_local_var(cmd, i, &content, &var);
		add_to_env(var, content, &g_locales);
		update_env_if_exist(var, content);
		ft_memdel((void**)&content);
		ft_memdel((void**)&var);
		i++;
	}
	return (0);
}

char			*return_local_content(char *name, t_list *env2)
{
	t_list	*v;
	char	flag;
	char	*content;

	flag = 0;
	content = NULL;
	v = (!g_locales && (++flag)) ? env2 : g_locales;
	while (v)
	{
		if (!ft_strcmp(((t_var*)v->data)->var, name))
			return (((t_var*)v->data)->content);
		v = v->next;
		if (!v && !flag && (++flag))
			v = (env2) ? env2 : NULL;
	}
	return (content);
}
