/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 20:50:12 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/29 20:58:58 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "g_col.h"

void	ft_wild(const char *str, int i, t_arg *ele, va_list ap)
{
	if (i == 0 || str[i - 1] != '.')
		ele->pad = va_arg(ap, int);
	else
	{
		ele->precision = va_arg(ap, int);
		if (ele->precision == 0)
			ele->precision = -1;
	}
	ele->wild = 1;
}

int		ft_precision(t_arg *ele, int i, const char *str)
{
	if (ft_isdigit(str[i + 1]))
	{
		ele->precision = ft_atoi(str + i + 1);
		if (ele->precision == 0)
			ele->precision = -1;
		while (str[++i] && ft_isdigit(str[i]))
			;
		--i;
	}
	else
		ele->precision = -1;
	return (i);
}

void	ft_flags_num(t_out *output, t_arg *ele)
{
	if (ele->hash && (ele->type == 'o' || ele->type == 'O'))
		ft_fill_out(output, "0", 1);
	else if (ele->hash && ((ele->format == 'u' && ele->data.u > 0)
				|| (ele->format == 'U' && ele->data.lu > 0)
				|| (ele->format == 'K' && ele->data.llu > 0)))
	{
		ft_fill_out(output, "0", 1);
		ft_fill_out(output, &ele->type, 1);
		ele->sharp = 1;
	}
	else if (((ele->type == 'i' || ele->type == 'd') && ele->data.d >= 0)
				|| (ele->type == 'D' && ele->data.ld >= 0)
				|| (ele->type == 'f' && ele->data.f >= 0.0))
	{
		if (ele->plus)
			ft_fill_out(output, "+", 1);
		else if (ele->space)
			ft_fill_out(output, " ", 1);
	}
}

void	ft_color(t_out *out, const char **str)
{
	int i;
	int	is_col;

	i = -1;
	is_col = 0;
	while (++i < 8)
	{
		if (!ft_strncmp(*str, g_coltab[i].str, g_coltab[i].len))
		{
			ft_fill_out(out, g_coltab[i].code, g_coltab[i].codelen);
			is_col = 1;
			break ;
		}
	}
	if (is_col)
	{
		while (**str != '}')
			*str += 1;
		*str += 1;
	}
}
