/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddcirc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 20:51:10 by apetitje          #+#    #+#             */
/*   Updated: 2017/05/25 16:56:36 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_lstaddcirc(t_list **alst, t_list *new)
{
	t_list *p;

	if (alst)
		if (new)
		{
			if (!*alst)
			{
				*alst = new;
				new->prev = new;
				new->next = new;
				new->last = 1;
			}
			else
			{
				p = (*alst)->prev;
				(*alst)->prev = new;
				new->next = *alst;
				*alst = new;
				new->prev = p;
			}
		}
}
