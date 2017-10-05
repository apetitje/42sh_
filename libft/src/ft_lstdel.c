/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 10:42:32 by apetitje          #+#    #+#             */
/*   Updated: 2017/01/14 16:46:39 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *next;

	next = NULL;
	if (alst)
	{
		if (*alst)
		{
			while (*alst != NULL)
			{
				next = (*alst)->next;
				del((*alst)->data, (*alst)->data_size);
				free(*alst);
				*alst = next;
			}
			alst = NULL;
		}
		free(alst);
	}
}
