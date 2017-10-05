/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 10:56:20 by apetitje          #+#    #+#             */
/*   Updated: 2017/01/02 12:22:15 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_lst;
	t_list	**end_lst;

	new_lst = NULL;
	end_lst = NULL;
	if (lst)
	{
		new_lst = f(lst);
		if (!new_lst)
			return (NULL);
		lst = lst->next;
		end_lst = &(new_lst->next);
		while (lst != NULL)
		{
			*end_lst = f(lst);
			if (!(*end_lst))
				return (NULL);
			end_lst = &((*end_lst)->next);
			lst = lst->next;
		}
	}
	return (new_lst);
}
