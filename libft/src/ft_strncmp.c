/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:40:59 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/27 12:16:10 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *a;
	unsigned char *b;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (n && *a && *b && *a == *b)
	{
		a++;
		b++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return (*a - *b);
}
