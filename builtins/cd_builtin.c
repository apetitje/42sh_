/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 15:48:54 by apetitje          #+#    #+#             */
/*   Updated: 2017/09/30 20:05:40 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*cd_home_old(int which, int *is_path,
		int *stat, t_list *env2)
{
	char	*path;
	char	*var;

	if (which == 0)
	{
		if (!(var = search_var_in_env(env2, "HOME")))
		{
			*stat = 6;
			return (NULL);
		}
		if (!(path = ft_strdup(var)))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
	}
	else
	{
		if (!(var = search_var_in_env(env2, "OLDPWD")))
		{
			*stat = 7;
			return (NULL);
		}
		if (!(path = ft_strdup(var)))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		*is_path = 1;
	}
	return (path);
}

static int	find_return_val(char **dir)
{
	if (convert_dir(dir) == 1 || is_dir(*dir) == -1)
		return (1);
	else if (is_dir(*dir) == 0)
		return (2);
	else if (access(*dir, X_OK))
		return (3);
	return (0);
}

static void	cd_error(int data[3], t_command *cmd, char **path)
{
	if (data[1] == 1)
		ft_dprintf(2, "42sh: cd: %s: No such file or directory\n",
				cmd->argv[data[2]]);
	else if (data[1] == 2)
		ft_dprintf(2, "42sh: cd: %s: Not a directory\n", cmd->argv[data[2]]);
	else if (data[1] == 3)
		ft_dprintf(2, "42sh: cd: %s: Permission denied\n", cmd->argv[data[2]]);
	else if (data[1] == 5)
		ft_dprintf(2,
				"42sh: cd: invalid option\ncd: usage: cd [-L|-P] [dir]\n");
	else if (data[1] == 6)
		ft_dprintf(2, "42sh: cd: HOME not set\n");
	else if (data[1] == 7)
		ft_dprintf(2, "42sh: cd: OLDPWD not set\n");
	else if (data[1] == -3)
	{
		ft_printf("%s\n", *path);
		data[1] = 0;
	}
}

static int	cd_end(t_command *command, int data[3], char **dir)
{
	char	w_dir[MAXPATHLEN + 1];
	int		bk_fd[3];

	getcwd(w_dir, MAXPATHLEN + 1);
	make_stdfd_bk((int*)bk_fd);
	if (do_redirect(command))
	{
		ft_memdel((void **)dir);
		restore_stdfd((int*)bk_fd);
		return (4);
	}
	cd_error(data, command, dir);
	if (data[1] == 0)
		change_dir(*dir, w_dir, data[0]);
	ft_memdel((void **)dir);
	restore_stdfd((int*)bk_fd);
	return (data[1]);
}

int			ft_cd(t_bt_args ar)
{
	char	*dir;
	int		is_path;
	int		data[3];

	is_path = 0;
	data[0] = 0;
	data[1] = 0;
	data[2] = 1;
	if (ar.cmd->argv[1] && ft_strcmp(ar.cmd->argv[1], "-"))
		dir = find_dir(ar.cmd, &is_path, data, ar.env);
	else
		dir = cd_home_old((ar.cmd->argv[1] ? 1 : 0),
				&is_path, &(data[1]), ar.env);
	if (!data[1])
		data[1] = find_return_val(&dir);
	if (data[1] == 0 && is_path)
		data[1] = -3;
	return (cd_end(ar.cmd, data, &dir));
}
