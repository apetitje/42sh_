/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 13:51:45 by apetitje          #+#    #+#             */
/*   Updated: 2017/03/04 00:25:18 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_end(char **strp, t_out *out, t_arg **ele, va_list ap)
{
	int			len;

	len = out->len;
	if (out->len > 0 && !(*strp = ft_memalloc(out->len + 1)))
		exit(EXIT_FAILURE);
	*strp = ft_memcpy(*strp, out->out, out->len);
	ft_free_ele(ele);
	ft_free_out(out);
	va_end(ap);
	return (len);
}

static void		ft_process_format(t_out *output, t_arg *ele)
{
	t_out		tmp;

	ft_init_out(&tmp);
	if (ele->type == 'f' || ele->type == 'F')
		ft_float(output, &tmp, ele);
	else if (ele->format == 'c' || ele->type == 's')
		ft_asalpha(output, &tmp, ele);
	else if (ele->type == 'C' || ele->type == 'S')
		ft_aswide(output, &tmp, ele);
	else if (ele->type == 'p')
		ft_point((unsigned long int)(ele->data.p), output, &tmp, ele);
	else if (ele->type == '%')
		ft_percent(output, &tmp, ele);
	else if (ft_strchr("hydDuULwK", ele->format))
		ft_num(output, &tmp, ele);
	else
		ft_nonspec(output, &tmp, ele);
}

int				ft_asprintf(char **strp, const char *format, ...)
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
	return (ft_end(strp, &output, &ele, ap));
}
