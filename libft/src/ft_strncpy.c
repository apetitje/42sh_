/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 01:25:17 by clabouri          #+#    #+#             */
/*   Updated: 2017/06/16 08:55:52 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	bmask(char *str)
{
	return (!(*(int*)str & 0xFF) || !(*(int*)str & 0xFF00)
			|| !(*(int*)str & 0xFF0000) || !(*(int*)str & 0xFF000000));
}

char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *t_s;

	t_s = dst;
	while (*src && len)
	{
		if (bmask((char*)src) || len < 4)
		{
			*(t_s++) = *(src++);
			len--;
		}
		else
		{
			*(((int*)t_s)) = *(((int*)src));
			t_s += 4;
			src += 4;
			len -= 4;
		}
	}
	*t_s = 0;
	return (dst);
}
