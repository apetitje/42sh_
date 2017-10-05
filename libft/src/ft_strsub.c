/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 18:35:55 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/27 12:22:54 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	index;

	if (!s)
		return (NULL);
	index = 0;
	if (!(dst = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (index < len)
	{
		dst[index] = s[start + index];
		index++;
	}
	dst[index] = '\0';
	return (dst);
}
