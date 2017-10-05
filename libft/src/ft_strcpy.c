/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 01:25:17 by clabouri          #+#    #+#             */
/*   Updated: 2017/10/02 00:47:25 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	bmask(char *str)
{
	return (!(*(long*)str & 0xFF) || !((*(long*)str << 8) & 0xFF)
			|| !(*(long*)str << 8 & 0xFF)
			|| !(*(long*)str << 16 & 0xFF)
			|| !(*(long*)str << 24 & 0xFF)
			|| !(*(long*)str << 32 & 0xFF)
			|| !(*(long*)str << 40 & 0xFF)
			|| !(*(long*)str << 48 & 0xFF));
}

char		*ft_strcpy(char *dest, const char *src)
{
	char *t_s;

	t_s = dest;
	while (!bmask((char*)src))
	{
		*(((long*)t_s)) = *(((long*)src));
		t_s += 8;
		src += 8;
	}
	while (*src)
		*(t_s++) = *(src++);
	*t_s = 0;
	return (dest);
}
