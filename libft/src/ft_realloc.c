/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 15:50:20 by apetitje          #+#    #+#             */
/*   Updated: 2017/05/09 19:08:48 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_realloc(void *ptr, size_t size, size_t old_size)
{
	void	*dup;

	dup = NULL;
	if (size)
	{
		if (!(dup = (char *)ft_memalloc(size)))
			return (NULL);
	}
	if (ptr && dup)
	{
		ft_memcpy(dup, ptr, old_size);
		*((char *)dup + old_size) = '\0';
		ft_memdel(&ptr);
	}
	(*(char *)(dup + size - 1)) = '\0';
	return (dup);
}
