/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:02:04 by clabouri          #+#    #+#             */
/*   Updated: 2017/08/08 05:28:02 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strchr(const char *s, int c)
{
	while (c)
	{
		if (!((*(int*)s ^ c) & 0xFF))
			return ((char*)s);
		if (!((*(int*)s ^ c << 8) & 0xFF00) && (ft_strlen(s) > 1))
			return ((char*)s + 1);
		if (!((*(int*)s ^ c << 16) & 0xFF0000) && (ft_strlen(s) > 2))
			return ((char*)s + 2);
		if (!((*(int*)s ^ c << 24) & 0xFF000000) && (ft_strlen(s) > 3))
			return ((char*)s + 3);
		if (!(*(int*)s & 0xFF) || !(*(int*)s & 0xFF00)
					|| !(*(int*)s & 0xFF0000) || !(*(int*)s & 0xFF000000))
			return (NULL);
		s += 4;
	}
	return ((char*)s + ft_strlen(s));
}

char	*ft_ostrchr(const char *s, int c)
{
	if (!c)
		return ((char*)s + ft_strlen(s));
	while (*s)
		if (*(s++) == c)
			return ((char*)s - 1);
	return (NULL);
}
