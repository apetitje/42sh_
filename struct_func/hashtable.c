/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 16:33:04 by hanguelk          #+#    #+#             */
/*   Updated: 2017/09/25 19:43:25 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		compute_key(char *s)
{
	int		i;

	i = 0;
	while (*s)
	{
		i *= 16777619;
		i ^= *s++;
	}
	return (i);
}

t_bckt	*init_bckt(char *skey, char *val, int hit)
{
	t_bckt	*bk;

	if (!(bk = (t_bckt *)malloc(sizeof(t_bckt))))
		exit_prog(EXIT_FAILURE, "Malloc error");
	bk->key = compute_key(skey);
	if (!(bk->data = ft_strdup(val)))
		exit_prog(EXIT_FAILURE, "Malloc error");
	if (!(bk->skey = ft_strdup(skey)))
		exit_prog(EXIT_FAILURE, "Malloc error");
	bk->next = NULL;
	bk->hits = hit;
	return (bk);
}

t_bckt	*hashtable_lookup(t_hashtable *ht, char *skey)
{
	t_bckt	*bk;
	int		hkey;

	if (!ht)
		return (NULL);
	hkey = compute_key(skey);
	bk = ht->table;
	while (bk)
	{
		if (bk->key == hkey)
		{
			bk->hits++;
			return (bk);
		}
		bk = bk->next;
	}
	return (NULL);
}
