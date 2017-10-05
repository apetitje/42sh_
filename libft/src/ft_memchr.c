/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:28:15 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/27 12:18:21 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *a;

	a = (unsigned char *)s;
	while (n)
	{
		if (*a == (unsigned char)c)
			return (a);
		a++;
		n--;
	}
	return (NULL);
}
