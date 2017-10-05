/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 17:25:26 by hanguelk          #+#    #+#             */
/*   Updated: 2017/10/01 18:52:33 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void	make_stdfd_bk(int *bk_fd)
{
	bk_fd[0] = dup(STDIN_FILENO);
	bk_fd[1] = dup(STDOUT_FILENO);
	bk_fd[2] = dup(STDERR_FILENO);
}

int		hashtable_print_data(char **elem)
{
	t_bckt	*tmp;
	int		res;

	res = 0;
	if (!*elem)
	{
		ft_dprintf(2, "42sh: hash: -t: option require and argument\n");
		display_hashusage(0);
		return (1);
	}
	if (*(elem + 1) == NULL)
	{
		if ((tmp = hashtable_lookup(&g_hash, elem[0])))
			ft_printf("%s\n", tmp->data);
		else
			res = hashtable_notfound(elem[0]);
	}
	else
		res = display_found(elem);
	return (res);
}

int		hashtable_removecell(char **elem)
{
	t_bckt	*tmp;
	int		r;

	tmp = g_hash.table;
	while (*elem)
	{
		if (!hashtable_remove(&g_hash, *elem))
			r = hashtable_notfound(*elem);
		elem++;
	}
	return (r);
}

int		hash_search(char **elem, t_list *env)
{
	char	*ex;
	t_path	path_struc;
	int		res;

	res = 0;
	path_struc.is_primary = 0;
	if (!(path_struc.path = build_path(env, "PATH")))
		ft_dprintf(2, "42sh: hash: PATH not found. Use -p pathname\n");
	while (*elem)
	{
		if ((ex = find_ex(*elem, path_struc)))
			ft_memdel((void**)&ex);
		else
			res = hashtable_notfound(*elem);
		elem++;
	}
	free_path(&path_struc.path);
	return (res);
}

void	restore_stdfd(int *bk_fd)
{
	dup2(bk_fd[0], STDIN_FILENO);
	dup2(bk_fd[1], STDOUT_FILENO);
	dup2(bk_fd[2], STDERR_FILENO);
	close(bk_fd[0]);
	close(bk_fd[1]);
	close(bk_fd[2]);
}
