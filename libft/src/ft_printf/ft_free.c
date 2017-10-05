/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 15:37:37 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/29 19:47:09 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_free_ele(t_arg **arg)
{
	if (arg && *arg)
	{
		free(*arg);
		*arg = NULL;
	}
}

void	ft_init_out(t_out *out)
{
	out->out = out->out1;
	out->stocked = 0;
	ft_bzero(out->out1, BUFFSIZE);
	out->len = 0;
}

void	ft_free_out(t_out *out)
{
	if (out->stocked)
	{
		free(out->out);
		out->out = out->out1;
	}
	out->stocked = 0;
	out->len = 0;
}
