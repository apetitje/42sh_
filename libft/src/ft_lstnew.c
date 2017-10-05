/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 10:21:52 by apetitje          #+#    #+#             */
/*   Updated: 2017/08/11 23:31:29 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_list	*ft_lstnew(void *data, size_t data_size)
{
	t_list	*lst;

	if (!data || !(lst = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	lst->data = data;
	lst->data_size = data_size;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

t_list	*ft_or_lstnew(const void *data, const size_t data_size)
{
	t_list *new;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	if (data)
	{
		if (!(new->data = malloc(data_size)))
			return (NULL);
		ft_memmove(new->data, data, data_size);
		new->data_size = data_size;
	}
	else
	{
		new->data = NULL;
		new->data_size = 0;
	}
	new->next = NULL;
	return (new);
}
