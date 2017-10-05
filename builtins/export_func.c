/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 15:42:58 by hanguelk          #+#    #+#             */
/*   Updated: 2017/10/03 20:15:45 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static int		export_usage(char opt)
{
	ft_dprintf(2, "42sh: export -%c: invalid option\n", opt);
	ft_dprintf(2, "export: usage: export [-pn] [name[=value] ...]\n");
	return (2);
}

void			adjust_list(t_list **ev, char flag, char gflag)
{
	if ((*ev)->prev)
		(*ev)->prev->next = (*ev)->next;
	else
	{
		if (!flag)
			g_env = (*ev)->next;
		else if (flag)
			g_exported = (*ev)->next;
		else if (gflag)
			g_locales = (*ev)->next;
	}
	if ((*ev)->next)
		(*ev)->next->prev = (*ev)->prev;
}

static int		dispatch_export(int opt, t_command *cmd, t_list *ev2, int i)
{
	int	j;
	int	res;

	res = 1;
	j = ft_tablen(cmd->argv) - i;
	if (opt == 2 && j > 0 && !g_currjob->pipeline)
		res = del_multi_var(cmd->argv, 0, 0);
	else if (opt == 1 && j > 0)
		res = export_variable(cmd, ev2, i);
	else if ((opt == 1 || opt == 2) && j == 0)
		res = export_all(ev2);
	else if (opt == 0 && j > 0)
		res = export_variable(cmd, ev2, i);
	return (res);
}

int				export_all(t_list *env)
{
	char flag;

	flag = 0;
	while (env)
	{
		ft_printf("export %s=\"%s\"\n", get_var(env), get_content(env));
		env = env->next;
		if (!env && !flag && (++flag))
			env = g_exported;
	}
	return (0);
}

int				parse_opt_export(t_command *cmd, t_list *env)
{
	int		opt;
	int		i;
	int		j;

	i = 0;
	opt = 0;
	while (++i && cmd->argv[i] && !(j = 0))
	{
		if (cmd->argv[i][j] == '-' && ++j)
		{
			while (cmd->argv[i][j])
			{
				if (cmd->argv[i][j] != 'p' && cmd->argv[i][j] != 'n')
					return (export_usage(cmd->argv[i][j]));
				else if (cmd->argv[i][j] == 'p' && opt != 2)
					opt = 1;
				else if (cmd->argv[i][j] == 'n')
					opt = 2;
				j++;
			}
		}
		else
			break ;
	}
	return (dispatch_export(opt, cmd, env, i));
}
