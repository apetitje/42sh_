/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 10:49:05 by apetitje          #+#    #+#             */
/*   Updated: 2017/05/08 20:52:45 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (alst)
		if (new)
		{
			if (!*alst)
				*alst = new;
			else
			{
				(*alst)->prev = new;
				new->next = *alst;
				*alst = new;
			}
		}
}
