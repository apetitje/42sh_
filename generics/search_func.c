/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 17:15:53 by apetitje          #+#    #+#             */
/*   Updated: 2017/06/26 00:10:53 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			is_exec(const char *ex)
{
	t_stat		stt;

	if (ex && stat(ex, &stt) != -1)
	{
		if ((stt.st_mode & S_IFMT) != S_IFREG)
			return (-1);
		if (!(stt.st_mode & S_IXUSR))
			return (-2);
		return (0);
	}
	return (-3);
}

size_t		find_size_max_from_list(t_list *list)
{
	size_t		size_max;

	size_max = 0;
	while (list)
	{
		if (ft_strlen(list->data) + 1 > size_max)
			size_max = ft_strlen(list->data) + 1;
		list = list->next;
	}
	return (size_max);
}

int			is_builtin(char *name)
{
	if (!ft_strcmp("exit", name))
		return (1);
	if (!ft_strcmp("echo", name))
		return (1);
	if (!ft_strcmp("env", name))
		return (1);
	if (!ft_strcmp("cd", name))
		return (1);
	if (!ft_strcmp("setenv", name))
		return (1);
	return (0);
}

char		*search_var_in_env(t_list *env, char *var)
{
	char		*content;

	content = NULL;
	while (env)
	{
		if (!ft_strcmp(get_var(env), var))
		{
			content = get_content(env);
			break ;
		}
		env = env->next;
	}
	return (content);
}

char		*exists_in_directory(char *dir_path, char *name)
{
	char		*path;
	DIR			*dir;
	t_dirent	*file;

	dir = NULL;
	path = NULL;
	if ((dir = opendir(dir_path)))
	{
		while ((file = readdir(dir)))
			if (!ft_strcmp(file->d_name, name))
			{
				ft_asprintf(&path, "%s/%s", dir_path, name);
				break ;
			}
		closedir(dir);
	}
	return (path);
}
