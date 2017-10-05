/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:38:59 by clabouri          #+#    #+#             */
/*   Updated: 2017/08/08 01:19:31 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	i = 0;
	if (dst > src)
		ft_memcpy(dst, src, len);
	else
		while (++i <= len)
			((char*)dst)[i - 1] = ((char*)src)[i - 1];
	return (dst);
}
