/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 12:38:17 by clabouri          #+#    #+#             */
/*   Updated: 2017/08/08 01:26:02 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	while (n > 0)
	{
		if (n >= 8)
		{
			n -= 8;
			*((long*)(dest + n)) = *((long*)(src + n));
		}
		else if (n >= 4)
		{
			n -= 4;
			*((int*)(dest + n)) = *((int*)(src + n));
		}
		else
		{
			n--;
			*((char*)(dest + n)) = *((char*)(src + n));
		}
	}
	return (dest);
}
