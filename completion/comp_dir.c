/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 15:21:46 by apetitje          #+#    #+#             */
/*   Updated: 2017/08/09 19:06:13 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static void		copy_file_name(int ret, char *name, t_list **matches)
{
	char		*ex;

	ex = NULL;
	if (ret == 0 && !(ex = ft_strdup(name)))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	else if (ret == -1)
		ft_asprintf(&ex, "%s/", name);
	ft_lstaddback(matches, ft_lstnew(ex, ft_strlen(ex)));
}

static void		find_dir_in_directory(char *dir_path, t_list **matches,
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
			if (!ft_strncmp(file->d_name, name, len))
			{
				ft_asprintf(&path, "%s/%s", dir_path, file->d_name);
				if (((ret = is_exec(path)) == -1)
						&& ft_strcmp(file->d_name, ".")
						&& ft_strcmp(file->d_name, ".."))
					copy_file_name(ret, file->d_name, matches);
				ft_memdel((void **)&path);
			}
		closedir(dir);
	}
}

void			comp_dir(t_list **mtch, char *to_find, size_t find_len,
		char **before)
{
	char		*name;
	char		*dir;
	char		*t;
	char		wd[MAXPATHLEN + 1];

	getcwd(wd, MAXPATHLEN + 1);
	if (!(dir = ft_strdup(to_find)))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	if ((name = ft_strrchr(to_find, '/')))
	{
		++name;
		dir[name - to_find] = '\0';
		t = *before;
		ft_asprintf(before, "%s%s", t, dir);
		ft_memdel((void **)&t);
		if (*dir == '~')
			expand_home_in_comp(&dir);
		find_dir_in_directory(dir, mtch, name, ft_strlen(name));
	}
	else
		find_dir_in_directory(wd, mtch, to_find, find_len);
	ft_memdel((void **)&dir);
}
