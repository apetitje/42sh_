/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 15:32:22 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/29 13:46:06 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_itoa_base(unsigned long int nb, t_arg *ele, t_out *tmp)
{
	char			num[100];
	int				i;
	char			*base_str;
	size_t			base;

	base_str = ft_init_base(ele->type, &base);
	i = 98;
	num[99] = '\0';
	while (nb >= base)
	{
		num[i] = base_str[nb % base];
		nb = nb / base;
		--i;
	}
	num[i] = base_str[nb];
	ele->len = 98 - i + 1;
	ft_fill_out(tmp, num + i, ele->len);
}
