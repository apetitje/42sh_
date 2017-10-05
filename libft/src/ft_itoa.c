/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 14:05:46 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/27 13:01:37 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_itoa(long long int n, t_arg *ele, t_out *tmp)
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
	ele->len = 98 - i + 1;
	ft_fill_out(tmp, inv + i, ele->len);
}
