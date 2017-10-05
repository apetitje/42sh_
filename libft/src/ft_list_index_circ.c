/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_index_circ.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 20:40:40 by apetitje          #+#    #+#             */
/*   Updated: 2017/03/21 18:52:01 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_list_index_circ(t_list *list)
{
	t_list	*ptr;
	int		index;

	index = 1;
	ptr = list;
	while (ptr)
	{
		ptr->index = index;
		if (ptr->last == 1)
			break ;
		ptr = ptr->next;
		++index;
	}
}
