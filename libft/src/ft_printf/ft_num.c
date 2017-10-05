/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:16:53 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 16:42:01 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_prec_num(t_arg *ele, t_out *tmp, t_out *flag)
{
	char		*ptr;
	int			len;

	ele->precision -= ele->len;
	if (flag->len > 0 && !ele->sharp && !ele->space && !ele->plus)
		ele->precision -= flag->len;
	if (tmp->len > 0 && *(tmp->out) == '-')
	{
		len = tmp->len - 1;
		ptr = ft_strndup(tmp->out + 1, len);
		ele->precision += 1;
		ft_free_out(tmp);
		ft_fill_out(tmp, "-", 1);
		while (ele->precision-- > 0)
			ft_fill_out(tmp, "0", 1);
		ft_fill_out(tmp, ptr, len);
		free(ptr);
	}
	while (ele->precision-- > 0)
		ft_join_before(tmp, "0", 1);
}

static void		ft_make_num(t_arg *ele, t_out *tmp, t_out *flag, t_out *out)
{
	if (ele->precision != -1)
		ft_prec_num(ele, tmp, flag);
	else if (flag->len == 0 || (ele->type != 'o' && ele->type != 'O'))
	{
		ele->padchar = ' ';
		if (ele->nul)
			ft_free_out(tmp);
	}
	ele->pad += ((ele->pad > 0) ? -flag->len : flag->len);
	if (ele->nul && (!ele->plus && !ele->space && flag->len > 0))
		ft_pad(tmp, 0, ele);
	else
		ft_pad(tmp, flag->out, ele);
	ft_fill_out(out, tmp->out, tmp->len);
}

void			ft_float(t_out *output, t_out *tmp, t_arg *ele)
{
	t_out		flag;

	ft_init_out(&flag);
	ft_flags_num(&flag, ele);
	if (ele->data.f != ele->data.f)
		ft_fill_out(tmp, "NaN", 3);
	else
	{
		if (ele->precision != -1 && ele->precision != 0)
			ele->data.f += ((ele->data.f < 0) ? -1 : 1)
				* ft_pow(10.0, -ele->precision) * 0.5;
		else if (!ele->hash && ele->precision != -1)
			ele->data.f += ((ele->data.f < 0) ? -1 : 1) * ft_pow(10.0, -6)
				* 0.5;
		else
			ele->data.f += ((ele->data.f < 0) ? -1 : 1) * 0.5;
		ft_dtoa(ele->data.f, (ele->precision > 0
					|| ele->precision == -1) ? ele->precision : 6, ele, tmp);
		if (ele->hash && ele->precision == -1)
			ft_fill_out(tmp, ".", 1);
	}
	ft_make_num(ele, tmp, &flag, output);
	ft_free_out(&flag);
	ft_free_out(tmp);
}

void			ft_num(t_out *output, t_out *tmp, t_arg *ele)
{
	t_out		flag;

	ft_init_out(&flag);
	ft_flags_num(&flag, ele);
	if (ele->format == 'd')
		ft_itoa(ele->data.d, ele, tmp);
	else if (ele->format == 'D')
		ft_itoa(ele->data.ld, ele, tmp);
	else if (ele->format == 'L')
		ft_itoa(ele->data.ll, ele, tmp);
	else if (ele->format == 'U')
		ft_itoa_base(ele->data.lu, ele, tmp);
	else if (ele->format == 'u')
		ft_itoa_base(ele->data.u, ele, tmp);
	else if (ele->format == 'w')
		ft_itoa_base(ele->data.uc, ele, tmp);
	else if (ele->format == 'K')
		ft_itoa_base(ele->data.llu, ele, tmp);
	ele->nul = (tmp->len > 0 && *(tmp->out) == '0') ? 1 : 0;
	ft_make_num(ele, tmp, &flag, output);
	ft_free_out(&flag);
	ft_free_out(tmp);
}
