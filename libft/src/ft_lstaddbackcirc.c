/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddbackcirc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 20:39:41 by apetitje          #+#    #+#             */
/*   Updated: 2017/03/21 12:04:52 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_lstaddbackcirc(t_list **alst, t_list *new)
{
	t_list	*ptr;

	if (alst)
	{
		ptr = *alst;
		if (new)
		{
			new->last = 1;
			if (!*alst)
			{
				*alst = new;
				(*alst)->next = *alst;
			}
			else
			{
				while (ptr->last != 1)
					ptr = ptr->next;
				ptr->last = 0;
				ptr->next = new;
				new->prev = ptr;
				new->next = *alst;
			}
			(*alst)->prev = new;
		}
	}
}
