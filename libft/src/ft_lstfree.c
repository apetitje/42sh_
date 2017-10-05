/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 02:10:50 by clabouri          #+#    #+#             */
/*   Updated: 2017/06/19 03:17:23 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_lstfree(t_list **lst)
{
	t_list	*tmp;

	if (!lst || !*lst)
		return ;
	while ((*lst)->next)
	{
		tmp = *lst;
		*lst = tmp->next;
		ft_lstfree_elem(&tmp);
	}
	ft_lstfree_elem(lst);
}
