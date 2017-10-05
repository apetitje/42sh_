/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 21:08:31 by clabouri          #+#    #+#             */
/*   Updated: 2017/06/19 03:31:07 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_lstswap(t_list *a, t_list *b)
{
	void *tmp;

	tmp = a->data;
	a->data = b->data;
	b->data = tmp;
}
