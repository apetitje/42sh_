/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:45:17 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/27 12:19:03 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	c = (char)c;
	if (c == '\0')
		return ((char *)s + len);
	s = s + len;
	while (len > 0 && *s != c)
	{
		len--;
		s--;
	}
	if (*s == c)
		return ((char *)s);
	else
		return (NULL);
}
