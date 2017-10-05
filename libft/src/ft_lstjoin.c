/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 16:18:05 by apetitje          #+#    #+#             */
/*   Updated: 2017/01/08 17:52:00 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_lstjoin(t_list *l1, t_list *l2)
{
	t_list	*ptr;

	ptr = l1;
	while (ptr && ptr->next)
		ptr = ptr->next;
	ptr->next = l2;
	if (l2)
		l2->prev = ptr;
}
