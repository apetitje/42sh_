/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:57:25 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/27 12:15:31 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t dlen;
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (i < size && dst[i] != '\0')
		i++;
	dlen = i;
	size = size - i;
	if (size == 0)
		return (i + ft_strlen(src));
	while (src[j])
	{
		if (size > 1)
		{
			dst[i] = src[j];
			size--;
			i++;
		}
		j++;
	}
	dst[i] = '\0';
	return (dlen + ft_strlen(src));
}
