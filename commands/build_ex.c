/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 17:04:35 by apetitje          #+#    #+#             */
/*   Updated: 2017/09/25 18:50:59 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

char	*find_ex(char *exec, t_path path_struc)
{
	char	*ex;
	int		i;
	char	w_dir[MAXPATHLEN + 1];

	ex = NULL;
	i = 0;
	getcwd(w_dir, MAXPATHLEN + 1);
	if ((*exec == '.' || ft_strchr(exec, '/')) &&
			ft_asprintf(&ex, "%s/%s", w_dir, exec))
		return (ex);
	if (!(path_struc.path) || !path_struc.path[0])
		ex = exists_in_directory(w_dir, exec);
	else
	{
		while (path_struc.path && path_struc.path[i])
		{
			if ((ex = exists_in_directory(path_struc.path[i], exec)))
				break ;
			++i;
		}
	}
	if (ex && !is_exec(ex) && !path_struc.is_primary)
		hashtable_add(&g_hash, exec, ex, 1);
	return (ex);
}

int		build_ex(t_command *command, char **ex, t_path path_struc, int *is_path)
{
	t_bckt	*ht;

	if (command->argv[0][0] == '/')
	{
		if (!(*ex = ft_strdup(command->argv[0])))
			exit_prog(EXIT_FAILURE, "Malloc error (build_ex)\n");
		*is_path = 1;
	}
	else if (!path_struc.is_primary
			&& (ht = hashtable_lookup(&g_hash, command->argv[0])))
	{
		if (!(*ex = ft_strdup(ht->data)))
			exit_prog(EXIT_FAILURE, "Malloc error (build_ex)\n");
	}
	else if (!(*ex = find_ex(command->argv[0], path_struc)))
		return ((ft_strchr(command->argv[0], '/')) ? -3 : -1);
	return (is_exec(*ex));
}
