/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 17:16:40 by hanguelk          #+#    #+#             */
/*   Updated: 2017/10/01 20:36:31 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int			display_hashtable(short flag)
{
	t_bckt	*bk;

	bk = g_hash.table;
	if (!g_hash.nbbckt)
	{
		ft_printf("hash: hash table empty\n");
		return (0);
	}
	if (!flag)
		ft_printf("hits\tcommand\n");
	while (bk)
	{
		if (!flag)
			ft_printf("%4d\t%s\n", bk->hits, bk->data);
		else
			ft_printf("builtin hash -p %s %s\n", bk->data, bk->skey);
		bk = bk->next;
	}
	return (0);
}

void		display_hashusage(char c)
{
	if (c)
		ft_dprintf(2, "42sh: hash: -%c: invalid option\n", c);
	ft_printf("hash: usage: hash [-lr] [-p pathname] [-dt] [name ...]\n");
}

int			hashtable_notfound(char *name)
{
	ft_dprintf(2, "hash: %s: not found\n", name);
	return (1);
}

int			display_found(char **elem)
{
	int		res;
	t_bckt	*tmp;

	res = 0;
	while (*elem)
	{
		if ((tmp = hashtable_lookup(&g_hash, *elem)))
			ft_printf("%s\t%s\n", *elem, tmp->data);
		else
			res = hashtable_notfound(elem[0]);
		elem++;
	}
	return (res);
}
