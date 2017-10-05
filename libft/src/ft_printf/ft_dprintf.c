/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 17:33:39 by apetitje          #+#    #+#             */
/*   Updated: 2017/01/12 17:45:55 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

static int		ft_end(int fd, t_out *out, t_arg **ele, va_list ap)
{
	int		len;

	len = out->len;
	write(fd, out->out, out->len);
	ft_free_ele(ele);
	ft_free_out(out);
	va_end(ap);
	return (len);
}

int				ft_dprintf(int fd, const char *format, ...)
{
	t_arg		*ele;
	va_list		ap;
	int			i;
	t_out		output;

	i = 0;
	ft_init_out(&output);
	va_start(ap, format);
	while ((ele = ft_print(&output, &format, ap)) != NULL)
	{
		if (ele->type != 'n')
			ft_process_format(&output, ele);
		++format;
		ft_free_ele(&ele);
	}
	return (ft_end(fd, &output, &ele, ap));
}
