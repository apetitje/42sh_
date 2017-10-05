/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 14:05:46 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/27 17:00:12 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_itoa1(long long int n)
{
	int					is_neg;
	unsigned long long	nb_cpy;
	char				inv[100];
	int					i;

	i = 98;
	is_neg = 0;
	if (n < 0)
		is_neg = 1;
	nb_cpy = (n < 0) ? (unsigned long long)-n : (unsigned long long)n;
	inv[99] = '\0';
	while (nb_cpy >= 10)
	{
		inv[i] = nb_cpy % 10 + 48;
		nb_cpy = nb_cpy / 10;
		--i;
	}
	inv[i] = nb_cpy + 48;
	if (is_neg == 1)
		inv[--i] = '-';
	return (ft_strdup(inv + i));
}

void			ft_dtoa(double n, int prec, t_arg *ele, t_out *tmp)
{
	int		i;
	char	*floor;
	char	*after;

	i = 0;
	if (prec == -1)
		ft_itoa((long long int)n, ele, tmp);
	else
	{
		floor = ft_itoa1((long long int)n);
		n = (n < 0) ? -(n - (long long int)n) : (n - (long long int)n);
		if (!(after = ft_memalloc(prec + 2)))
			exit(EXIT_FAILURE);
		after[0] = '.';
		while (++i <= prec)
		{
			after[i] = (int)(n * 10) + 48;
			n = n * 10 - (int)(n * 10);
		}
		ele->len += ft_strlen(floor) + ft_strlen(after);
		ft_fill_out(tmp, floor, ft_strlen(floor));
		ft_fill_out(tmp, after, ft_strlen(after));
		free(after);
		free(floor);
	}
}
