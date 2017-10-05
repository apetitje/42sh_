/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 19:08:05 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 13:53:40 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int			is_dir(const char *dir)
{
	t_stat	stt;

	if (dir && access(dir, F_OK) != -1 && stat(dir, &stt) != -1)
	{
		if ((stt.st_mode & S_IFMT) != S_IFDIR)
			return (0);
		return (1);
	}
	return (-1);
}

void		change_dir(char *path, char w_dir[], int flag)
{
	size_t	len;

	if (!path)
		return ;
	if (!g_currjob->pipeline)
	{
		len = ft_strlen(path) - 1;
		chdir(path);
		add_to_env("OLDPWD", w_dir, &g_env);
		if (len != 0 && path[len] == '/')
			path[len] = '\0';
		if (flag != 'P')
			add_to_env("PWD", path, &g_env);
		else
		{
			getcwd(w_dir, MAXPATHLEN + 1);
			add_to_env("PWD", w_dir, &g_env);
		}
	}
}

static int	find_flag(t_command *command, int *j, int d[3])
{
	int		i;

	while (command->argv[*j] && command->argv[*j][0] == '-')
	{
		i = 1;
		if (!command->argv[*j][i] ||
				(command->argv[*j][i] == '-' && !command->argv[*j][i + 1]))
			return (0);
		while (command->argv[*j][i])
		{
			if (command->argv[*j][i] == 'L'
					|| command->argv[*j][i] == 'P')
				d[0] = command->argv[*j][i];
			else
				return (1);
			++i;
		}
		++(*j);
	}
	d[2] = *j;
	return (0);
}

static char	*init_dir(char **dir, int *j, char w_dir[])
{
	*dir = NULL;
	*j = 1;
	getcwd(w_dir, MAXPATHLEN + 1);
	return (search_var_in_env(g_env, "PWD"));
}

char		*find_dir(t_command *comm, int *is_path, int d[3], t_list *env2)
{
	char	*dir;
	int		j;
	char	w_dir[MAXPATHLEN + 1];
	char	*curr_dir;

	curr_dir = init_dir(&dir, &j, w_dir);
	if (comm->argv[j][0] == '-' && find_flag(comm, &j, d) && (d[1] = 5))
		return (NULL);
	curr_dir = (d[0] || !curr_dir) ? w_dir : curr_dir;
	if (!comm->argv[j] || comm->argv[j][0] == '-')
		return (cd_home_old((comm->argv[j] ? 1 : 0), is_path, &(d[1]), env2));
	if (comm->argv[j][0] == '.')
		ft_asprintf(&dir, "%s/%s", curr_dir, comm->argv[j]);
	else if (comm->argv[j][0] != '/')
	{
		if (!(dir = find_in_path(comm, is_path, env2)))
			ft_asprintf(&dir, "%s/%s", curr_dir, comm->argv[j]);
	}
	else if (!(dir = ft_strdup(comm->argv[j])))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	return (dir);
}
