/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_ex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 19:04:33 by apetitje          #+#    #+#             */
/*   Updated: 2017/08/09 19:26:12 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static void	copy_file_name(int ret, char *name, t_list **matches)
{
	char		*ex;

	ex = NULL;
	if (ret == 0 && !(ex = ft_strdup(name)))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	else if (ret == -1)
		ft_asprintf(&ex, "%s/", name);
	ft_lstaddback(matches, ft_lstnew(ex, ft_strlen(ex)));
}

void		find_ex_in_directory(char *dir_path, t_list **matches,
		char *name, size_t len)
{
	DIR			*dir;
	t_dirent	*file;
	char		*path;
	int			ret;

	path = NULL;
	if ((dir = opendir(dir_path)))
	{
		while ((file = readdir(dir)))
			if (!ft_strncmp(file->d_name, name, len)
					&& !is_builtin(file->d_name))
			{
				ft_asprintf(&path, "%s/%s", dir_path, file->d_name);
				if (((ret = is_exec(path)) == 0 || ret == -1)
						&& ft_strcmp(file->d_name, ".")
						&& ft_strcmp(file->d_name, ".."))
					copy_file_name(ret, file->d_name, matches);
				ft_memdel((void **)&path);
			}
		closedir(dir);
	}
}

static void	find_in_builtins_bis(t_list **matches, char *name,
		size_t len, char *ex)
{
	if (!ft_strncmp("setenv", name, len))
	{
		if (!(ex = ft_strdup("setenv")))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		ft_lstaddback(matches, ft_lstnew(ex, sizeof(ex)));
	}
	if (!ft_strncmp("unsetenv", name, len))
	{
		if (!(ex = ft_strdup("unsetenv")))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		ft_lstaddback(matches, ft_lstnew(ex, sizeof(ex)));
	}
	if (!ft_strncmp("hash", name, len))
	{
		if (!(ex = ft_strdup("hash")))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		ft_lstaddback(matches, ft_lstnew(ex, sizeof(ex)));
	}
	if (!ft_strncmp("cd", name, len))
	{
		if (!(ex = ft_strdup("cd")))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		ft_lstaddback(matches, ft_lstnew(ex, sizeof(ex)));
	}
}

void		find_in_builtins(t_list **matches, char *name, size_t len,
		char **dir)
{
	char	*ex;

	ft_memdel((void **)dir);
	if (!ft_strncmp("exit", name, len))
	{
		if (!(ex = ft_strdup("exit")))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		ft_lstaddback(matches, ft_lstnew(ex, sizeof(ex)));
	}
	if (!ft_strncmp("echo", name, len))
	{
		if (!(ex = ft_strdup("echo")))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		ft_lstaddback(matches, ft_lstnew(ex, sizeof(ex)));
	}
	if (!ft_strncmp("env", name, len))
	{
		if (!(ex = ft_strdup("env")))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		ft_lstaddback(matches, ft_lstnew(ex, sizeof(ex)));
	}
	find_in_builtins_bis(matches, name, len, ex);
}

void		complete_first(t_list **mtch, char *to_find, size_t find_len,
		char **before)
{
	char	**path;
	char	*name;
	char	*dir;
	int		i;
	char	*t;

	if (!(dir = ft_strdup(to_find)))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	path = build_path(g_env, "PATH");
	if ((name = ft_strrchr(to_find, '/')))
	{
		++name;
		dir[name - to_find] = '\0';
		t = *before;
		ft_asprintf(before, "%s%s", t, dir);
		ft_memdel((void **)&t);
		if (*dir == '~')
			expand_home_in_comp(&dir);
		find_ex_in_directory(dir, mtch, name, ft_strlen(name));
	}
	i = -1;
	while (path && path[++i])
		find_ex_in_directory(path[i], mtch, to_find, find_len);
	free_path(&path);
	find_in_builtins(mtch, to_find, find_len, &dir);
}
