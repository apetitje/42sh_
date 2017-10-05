/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 02:10:50 by clabouri          #+#    #+#             */
/*   Updated: 2017/06/16 08:50:41 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_lstfree_elem(t_list **lst)
{
	if (!lst)
		return ;
	ft_memdel(&((*lst)->data));
	ft_memdel((void**)lst);
}
