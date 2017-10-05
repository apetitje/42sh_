/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 01:25:02 by clabouri          #+#    #+#             */
/*   Updated: 2017/06/26 00:09:39 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i1;
	int	i2;
	int mi;

	i1 = ft_strlen(s1);
	i2 = ft_strlen(s2);
	while (i1 && i2)
	{
		if (*s1 != *s2)
			break ;
		if (i1 >= 8 && i2 >= 8 && !(*(long*)s1 ^ *(long*)s2))
			mi = 8;
		else if (i1 >= 4 && i2 >= 4 && !(*(int*)s1 ^ *(int*)s2))
			mi = 4;
		else
			mi = 1;
		s1 += mi;
		s2 += mi;
		i1 -= mi;
		i2 -= mi;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}
