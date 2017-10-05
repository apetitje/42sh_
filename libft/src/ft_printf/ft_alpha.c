/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alpha.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:49:48 by apetitje          #+#    #+#             */
/*   Updated: 2017/03/07 09:45:27 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_alpha(t_out *output, t_out *tmp, t_arg *ele)
{
	char		*s;

	s = ele->data.p;
	if (ele->type == 'c')
		ft_fill_out(tmp, &(ele->data.c), 1);
	else if (ele->type == 's' && ele->precision != -1)
	{
		if (s)
		{
			ele->len = ft_strlen(s);
			if (ele->len > ele->precision && ele->precision > 0)
				ele->len = ele->precision;
			ft_fill_out(tmp, s, ele->len);
		}
	}
	if (ele->pad != 0)
		ft_pad(tmp, 0, ele);
	ft_fill_out(output, tmp->out, tmp->len);
	ft_free_out(tmp);
}

void			ft_asalpha(t_out *output, t_out *tmp, t_arg *ele)
{
	char		*s;

	s = ele->data.p;
	if (ele->type == 'c')
	{
		if (!(ele->data.c))
			return ;
		ft_fill_out(tmp, &(ele->data.c), 1);
	}
	else if (ele->type == 's' && ele->precision != -1)
	{
		if (s)
		{
			ele->len = ft_strlen(s);
			if (ele->len > ele->precision && ele->precision > 0)
				ele->len = ele->precision;
			ft_fill_out(tmp, s, ele->len);
		}
		else
			return ;
	}
	if (ele->pad != 0)
		ft_pad(tmp, 0, ele);
	ft_fill_out(output, tmp->out, tmp->len);
	ft_free_out(tmp);
}

void			ft_aswide(t_out *output, t_out *tmp, t_arg *ele)
{
	wchar_t		*ls;
	int			put;

	put = 0;
	if (ele->type == 'C')
	{
		ls = &(ele->data.lc);
		ele->len = 1;
	}
	else
	{
		ls = (wchar_t *)(ele->data.p);
		if (ls)
			ele->len = ft_wide_strlen(ls);
		else
			return ;
	}
	while (ele->len > 0 && (ele->type == 'C' || (ele->type == 'S'
					&& (ele->precision < 1 || put < ele->precision))))
		ft_print_wide(tmp, ele, &ls, &put);
	(ele->type == 'S' && ele->precision == -1) ? ft_free_out(tmp) : 0;
	(ele->pad != 0) ? ft_pad(tmp, 0, ele) : 0;
	ft_fill_out(output, tmp->out, tmp->len);
}
