/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 16:06:52 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/05 02:12:33 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static t_builtins_tuple	*s_get_bt_list(void)
{
	static t_builtins_tuple builtins[] = {
			{ "cd", ft_cd },
			{ "echo", ft_echo },
			{ "env", get_env },
			{ "setenv", set_env },
			{ "unsetenv", unset_env },
			{ "exit", exit_func },
			{ "hash", ft_hash },
			{ "history", builtin_history },
			{ "jobs", ft_jobs },
			{ "fg", fg_jobs },
			{ "bg", bg_jobs },
			{ "export", bt_export},
			{ "unset", unset_bt},
			{ "read", bt_read},
			{ "dispvars", bt_nanoset}
	};

	return ((t_builtins_tuple*)builtins);
}

static int				do_exec(t_command *command, int code, t_list *env2)
{
	char	**environ;
	int		ret;
	t_path	path_struc;

	environ = build_env(env2);
	path_struc.path = build_path(env2, "PATH");
	path_struc.is_primary = 0;
	ret = open_exec(command, environ, path_struc, code);
	free_path(&path_struc.path);
	return (ret);
}

static int				find_in_builtins(t_command *command,
		const t_builtins_tuple *builtins, t_list *env2)
{
	size_t					i;
	int						res;
	t_bt_args				btargs;

	i = 0;
	res = -1337;
	while (i < NBBUILTINS)
	{
		if (ft_strequ(command->argv[0], builtins[i].name))
		{
			g_currjob->pgid = (i == 2 || g_currjob->subsh) ?
				g_currjob->pgid : -1;
			btargs.cmd = command;
			btargs.env = env2;
			res = builtins[i].func(btargs);
			break ;
		}
		++i;
	}
	return (res);
}

static void				find_command_locales(t_command *command, t_list **env2)
{
	size_t	i;
	char	*equal;
	char	*tmp;

	i = 0;
	while (command->locales && command->locales[i] &&
			(equal = ft_strchr(command->locales[i], '=')))
	{
		ft_asprintf(&tmp, "%.*s", equal - command->locales[i],
				command->locales[i]);
		equal += 1;
		if (tmp && *tmp)
		{
			if (!ft_strcmp(tmp, "PATH") && !ft_strcmp(command->argv[0], "hash"))
				hashtable_free(&g_hash);
			add_to_env(tmp, equal, env2);
			ft_memdel((void **)&tmp);
		}
		++i;
	}
}

int						do_command(t_command *command, int code)
{
	t_builtins_tuple		*builtins;
	int						res;
	t_list					*env2;

	builtins = s_get_bt_list();
	env2 = copy_env(g_env);
	find_command_locales(command, &env2);
	g_currjob->code = (!g_currjob->subsh) ? code : g_currjob->code;
	if (command->argc < 1)
		return (1);
	res = find_in_builtins(command, builtins, env2);
	if (res == -1337)
		res = do_exec(command, code, env2);
	free_env(&env2);
	return (res);
}
