/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoac.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:40:31 by apetitje          #+#    #+#             */
/*   Updated: 2017/09/28 19:40:33 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_size(int n)
{
	size_t i;

	if (!n)
		return (1);
	i = 0;
	while ((n /= 10))
		i++;
	return (i + 1);
}

char			*ft_itoac(int n)
{
	char				*ret;
	unsigned int		nb;
	int					i;
	size_t				size;

	i = 0;
	nb = (n < 0) ? -n : n;
	size = (n < 0) ? get_size(nb) + 1 : get_size(nb);
	if (!(ret = ft_strnew(size)))
		return (NULL);
	while (nb)
	{
		ret[i++] = (nb % 10) + 48;
		nb /= 10;
	}
	if (!n)
		ret[i] = 48;
	if (n < 0)
		ret[i] = '-';
	return (ft_strrev(ret));
}
