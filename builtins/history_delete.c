/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:14:48 by oyagci            #+#    #+#             */
/*   Updated: 2017/09/27 10:09:57 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static int		get_offset(char *value)
{
	if (!value)
		return (-1);
	return (ft_atoi(value));
}

static void		remove_hist_elem(t_list *elem)
{
	t_list *old;

	old = elem;
	if (elem && elem->next)
		elem->next->prev = elem->prev;
	if (elem && elem->prev)
		elem->prev->next = elem->next;
	else if (elem)
		g_hist = elem->next;
	if (old)
	{
		free(get_hist(old));
		free(old->data);
		free(old);
	}
}

int				print_outofrange(void)
{
	ft_dprintf(2, "history: index out of range\n");
	return (1);
}

int				history_delete(t_hist_opt *opt)
{
	int		offset;
	int		j;
	t_list	*head;

	if (-1 == (offset = get_offset(opt->value)))
	{
		ft_dprintf(2, "history: missing offset specifier\n");
		return (1);
	}
	j = 1;
	head = g_hist;
	while (head && head->next)
		head = head->next;
	while (j < offset && head && head->prev)
	{
		head = head->prev;
		j += 1;
	}
	if (j == offset)
		remove_hist_elem(head);
	else
		return (print_outofrange());
	return (0);
}
