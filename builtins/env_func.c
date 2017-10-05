/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 18:39:38 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 12:23:19 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static int	free_env_and_path(t_list **env2, t_path *path_struc, int *bk_fd)
{
	free_env(env2);
	free_path(&path_struc->path);
	restore_stdfd(bk_fd);
	return (0);
}

static	int	env_usage(t_list **env2, t_path *path_struc, int *bk_fd)
{
	ft_dprintf(2, "env: illegal option\nusage: env [-i]\n");
	ft_dprintf(2, "           [utility [argument ...]]\n");
	free_env_and_path(env2, path_struc, bk_fd);
	return (1);
}

static int	env_end(t_command *command, int empty, t_list **env2,
		t_path *path_struc)
{
	char	**environ;
	int		ret;
	t_list	*redirs_bk;
	int		bk_fd[3];

	make_stdfd_bk((int*)bk_fd);
	if (do_redirect(command))
	{
		free_env_and_path(env2, path_struc, (int*)bk_fd);
		return (1);
	}
	if (empty == -1)
		return (env_usage(env2, path_struc, (int*)bk_fd));
	if (!command->argv[0] && print_env(*env2))
		return (free_env_and_path(env2, path_struc, (int*)bk_fd));
	environ = build_env(*env2);
	g_currjob->subsh = (g_currjob->subsh) ? 2 : 0;
	redirs_bk = command->redirs;
	command->redirs = NULL;
	ret = open_exec(command, environ, *path_struc, g_currjob->code);
	command->redirs = redirs_bk;
	free_env_and_path(env2, path_struc, (int*)bk_fd);
	return (ret);
}

int			get_env(t_bt_args ar)
{
	int			empty;
	t_list		*env2;
	t_path		path_struc;
	int			j;

	empty = 0;
	j = 1;
	path_struc.path = build_path(ar.env, "PATH");
	path_struc.is_primary = 1;
	if (ar.cmd->argv[j] && ar.cmd->argv[j][0] == '-')
		find_env_flags(ar.cmd, &j, &empty);
	env2 = (empty) ? NULL : copy_env(ar.env);
	find_locales(ar.cmd, &j, &env2, &path_struc);
	new_argv(ar.cmd, j);
	return (env_end(ar.cmd, empty, &env2, &path_struc));
}
