/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 01:25:35 by clabouri          #+#    #+#             */
/*   Updated: 2017/10/02 01:25:28 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(char const *s)
{
	char *t_s;

	t_s = (char*)s;
	while (1)
	{
		if (!(*(long*)t_s & 0xFF))
			return (t_s - s);
		if (!(*(long*)t_s & 0xFF00))
			return (t_s - s + 1);
		if (!(*(long*)t_s & 0xFF0000))
			return (t_s - s + 2);
		if (!(*(long*)t_s & 0xFF000000))
			return (t_s - s + 3);
		if (!(*(long*)t_s & 0xFF00000000))
			return (t_s - s + 4);
		if (!(*(long*)t_s & 0xFF0000000000))
			return (t_s - s + 5);
		if (!(*(long*)t_s & 0xFF000000000000))
			return (t_s - s + 6);
		if (!(*(long*)t_s & 0xFF00000000000000))
			return (t_s - s + 7);
		t_s += 8;
	}
}
