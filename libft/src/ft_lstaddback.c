/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 12:05:30 by apetitje          #+#    #+#             */
/*   Updated: 2017/01/09 18:33:33 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_lstaddback(t_list **alst, t_list *new)
{
	t_list	*ptr;

	if (alst)
	{
		ptr = *alst;
		if (new)
		{
			if (!*alst)
				*alst = new;
			else
			{
				while (ptr->next != NULL)
					ptr = ptr->next;
				ptr->next = new;
				new->prev = ptr;
			}
		}
	}
}
