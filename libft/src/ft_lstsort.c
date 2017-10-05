/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 20:50:01 by clabouri          #+#    #+#             */
/*   Updated: 2017/06/19 03:31:09 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_lstsort(t_list *lst, int (*cmp)(void*, void*))
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!(tmp = lst))
		return ;
	while ((tmp2 = tmp->next))
	{
		if (cmp(tmp->data, tmp2->data) > 0)
		{
			ft_lstswap(tmp, tmp2);
			tmp = lst;
			continue ;
		}
		tmp = tmp->next;
	}
}
