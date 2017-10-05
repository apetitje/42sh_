/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:14:33 by hanguelk          #+#    #+#             */
/*   Updated: 2017/10/03 20:15:10 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int			check_valid_identifier(char *id)
{
	int		i;

	i = -1;
	if (!ft_isalpha(id[++i]))
	{
		ft_dprintf(2, "42sh: export %s: Not a valid identifier.\n", id);
		return (-1);
	}
	while (id[++i] && id[i] != '=')
	{
		if (!ft_isalpha(id[i]) && !ft_isdigit(id[i]) && id[i] != '_')
		{
			ft_dprintf(2, "42sh: export %s: Not a valid identifier.\n", id);
			return (-1);
		}
	}
	return (i);
}

int			del_multi_var(char **var, char gflag, char flag)
{
	t_list	*ev;
	t_list	*tmp;

	while (*var && !(flag = 0))
	{
		ev = (gflag) ? g_locales : g_env;
		(!ft_strcmp("PATH", *var)) ? hashtable_free(&g_hash) : 0;
		if (!ft_strcmp(*var, "?"))
			break ;
		while (ev)
		{
			if (!ft_strcmp(get_var(ev), *var) && (tmp = ev))
			{
				adjust_list(&ev, flag, gflag);
				if (!g_currjob->pipeline)
					unset_var(&tmp);
				break ;
			}
			ev = ev->next;
			if (!ev && !gflag && !flag && (++flag))
				ev = g_exported;
		}
		var++;
	}
	return (0);
}

static	int	parse_and_add(char *args)
{
	int		i;
	char	*nme;
	char	*content;

	content = NULL;
	if ((i = check_valid_identifier(args)) < 0)
		return (1);
	if (!(nme = ft_strndup(args, i)))
		exit_prog(EXIT_FAILURE, "Malloc error.\n");
	(!ft_strcmp("PATH", nme)) ? hashtable_free(&g_hash) : 0;
	if (args + i + 1)
		if (!(content = ft_strdup(args + i + 1)))
			exit_prog(EXIT_FAILURE, "Malloc error.\n");
	if (content)
	{
		if (!g_currjob->pipeline)
			add_to_env(nme, content, &g_env);
		ft_memdel((void**)&content);
	}
	ft_memdel((void**)&nme);
	return (0);
}

int			export_variable(t_command *args, t_list *env2, int j)
{
	int		r;
	char	*content;

	r = 0;
	while (j < args->argc)
	{
		if (ft_strchr(args->argv[j], '='))
			r = parse_and_add(args->argv[j]);
		else
		{
			if (check_valid_identifier(args->argv[j]) < 0)
				r = 1;
			else
			{
				if ((content = return_local_content(args->argv[j], env2)) &&
						!g_currjob->pipeline)
					add_to_env(args->argv[j], content, &g_env);
				else if (!g_currjob->pipeline)
					add_to_env(args->argv[j], "", &g_exported);
			}
		}
		j++;
	}
	return (r);
}

int			bt_export(t_bt_args ar)
{
	int			bk_fd[3];
	int			res;

	res = 0;
	make_stdfd_bk((int*)bk_fd);
	if (do_redirect(ar.cmd))
	{
		restore_stdfd((int*)bk_fd);
		return (1);
	}
	if (ar.cmd->argc == 1)
		export_all(ar.env);
	else
		res = parse_opt_export(ar.cmd, ar.env);
	restore_stdfd((int*)bk_fd);
	return (res);
}
