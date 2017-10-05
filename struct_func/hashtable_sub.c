/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 19:40:58 by hanguelk          #+#    #+#             */
/*   Updated: 2017/10/01 18:37:17 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

t_hashtable	*init_hashtable(void)
{
	t_hashtable	*ht;

	if (!(ht = (t_hashtable *)malloc(sizeof(t_hashtable))))
		exit_prog(EXIT_FAILURE, "Malloc error");
	ht->nbbckt = 0;
	ht->table = NULL;
	return (ht);
}

t_bckt		*hashtable_add(t_hashtable *ht, char *skey, char *value, int hit)
{
	t_bckt	*mesh;
	t_bckt	*bk;

	if ((bk = hashtable_lookup(ht, skey)))
	{
		bk->hits = 0;
		return (bk);
	}
	mesh = init_bckt(skey, value, hit);
	if (!ht->table)
		ht->table = mesh;
	else
	{
		bk = ht->table;
		while (bk->next)
			bk = bk->next;
		bk->next = mesh;
	}
	ht->nbbckt++;
	return (mesh);
}

int			hashtable_delmesh(t_bckt *bk)
{
	ft_memdel((void**)&bk->data);
	ft_memdel((void**)&bk->skey);
	bk->key = 0;
	ft_memdel((void**)&bk);
	return (1);
}

int			hashtable_free(t_hashtable *ht)
{
	t_bckt	*tmp;
	t_bckt	*bk;

	tmp = ht->table;
	while (tmp)
	{
		bk = tmp->next;
		hashtable_delmesh(tmp);
		tmp = bk;
	}
	ht->table = NULL;
	ht->nbbckt = 0;
	return (0);
}

int			hashtable_remove(t_hashtable *ht, char *skey)
{
	int		key;
	int		r;
	t_bckt	*bk;
	t_bckt	*prev;

	r = 0;
	key = compute_key(skey);
	bk = ht->table;
	if (bk && bk->key == key && ++r && ht->nbbckt--)
	{
		ht->table = bk->next;
		hashtable_delmesh(bk);
		bk = ht->table;
	}
	while (bk)
	{
		if (bk->key == key && ++r && ht->nbbckt--)
			((prev->next = bk->next) || 1) ? hashtable_delmesh(bk) : 0;
		else
			prev = bk;
		bk = prev->next;
	}
	return (r);
}
