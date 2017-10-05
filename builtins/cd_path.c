/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 18:02:10 by apetitje          #+#    #+#             */
/*   Updated: 2017/06/07 20:06:12 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*find_in_path(t_command *command, int *is_path, t_list *env2)
{
	char	**search_path;
	char	*dir;
	int		i;

	i = 0;
	dir = NULL;
	search_path = NULL;
	search_path = build_path(env2, "CDPATH");
	while (search_path && search_path[i])
	{
		ft_asprintf(&dir, "%s/%s", search_path[i], command->argv[1]);
		if (is_dir(dir) == 1)
		{
			*is_path = 1;
			break ;
		}
		ft_memdel((void **)&dir);
		++i;
	}
	free_path(&search_path);
	return (dir);
}
