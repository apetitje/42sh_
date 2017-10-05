/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 13:51:45 by apetitje          #+#    #+#             */
/*   Updated: 2017/03/04 00:29:14 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_init_arg(t_arg *new_ele)
{
	new_ele->nul = 0;
	new_ele->precision = 0;
	new_ele->padleft = 0;
	new_ele->pad = 0;
	new_ele->len = 0;
	new_ele->padchar = ' ';
	new_ele->hash = 0;
	new_ele->plus = 0;
	new_ele->space = 0;
	new_ele->wild = 0;
	new_ele->zero = 0;
	new_ele->unsign = 0;
	new_ele->sharp = 0;
	new_ele->modifier = 0;
}

static void		ft_process_format(t_out *output, t_arg *ele)
{
	t_out		tmp;

	ft_init_out(&tmp);
	if (ele->type == 'f' || ele->type == 'F')
		ft_float(output, &tmp, ele);
	else if (ele->format == 'c' || ele->type == 's')
		ft_alpha(output, &tmp, ele);
	else if (ele->type == 'C' || ele->type == 'S')
		ft_wide(output, &tmp, ele);
	else if (ele->type == 'p')
		ft_point((unsigned long int)(ele->data.p), output, &tmp, ele);
	else if (ele->type == '%')
		ft_percent(output, &tmp, ele);
	else if (ft_strchr("hydDuULwK", ele->format))
		ft_num(output, &tmp, ele);
	else
		ft_nonspec(output, &tmp, ele);
}

t_arg			*ft_arg(void)
{
	t_arg		*new_ele;

	if (!(new_ele = malloc(sizeof(t_arg))))
		exit(EXIT_FAILURE);
	ft_init_arg(new_ele);
	return (new_ele);
}

static int		ft_end(t_out *out, t_arg **ele, va_list ap)
{
	int		len;

	len = out->len;
	write(1, out->out, out->len);
	ft_free_ele(ele);
	ft_free_out(out);
	va_end(ap);
	return (len);
}

int				ft_printf(const char *format, ...)
{
	t_arg		*ele;
	va_list		ap;
	t_out		output;

	ft_init_out(&output);
	va_start(ap, format);
	while ((ele = ft_print(&output, &format, ap)) != NULL)
	{
		if (ele->type != 'n')
			ft_process_format(&output, ele);
		++format;
		ft_free_ele(&ele);
	}
	return (ft_end(&output, &ele, ap));
}
