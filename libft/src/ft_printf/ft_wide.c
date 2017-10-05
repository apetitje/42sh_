/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 12:01:56 by apetitje          #+#    #+#             */
/*   Updated: 2017/03/04 00:18:50 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_widesize(wchar_t c)
{
	if (c < 0x80)
		return (1);
	if (c < 0x800)
		return (2);
	if (c < 0x10000)
		return (3);
	if (c <= 0x1FFFFF)
		return (4);
	if (c <= 0x3FFFFFF)
		return (5);
	if (c <= 0x7FFFFFFF)
		return (6);
	return (0);
}

static void		ft_bit_mask(int decalage, wchar_t c, char *ch, size_t size)
{
	if (size == 5)
		*ch = 0x80 + ((c & 0xf000000) >> decalage);
	if (size == 4)
		*ch = 0x80 + ((c & 0xfc0000) >> decalage);
	if (size == 3)
		*ch = 0x80 + ((c & 0x3f000) >> decalage);
	if (size == 2)
		*ch = 0x80 + ((c & 0x0fc0) >> decalage);
	if (size == 1)
		*ch = 0x80 + (c & 0x3f);
}

static void		ft_putwide(t_out *output, wchar_t c, size_t size, int decalage)
{
	char		ch;

	ch = 0;
	if (size == 6)
		ch = 0xfc + ((c & 0x40000000) >> decalage);
	else if (size == 5)
		ch = 0xf8 + ((c & 0x3000000) >> decalage);
	else if (size == 4)
		ch = 0xf0 + ((c & 0x1c0000) >> decalage);
	else if (size == 3)
		ch = 0xe0 + ((c & 0xf000) >> decalage);
	else if (size == 2)
		ch = 0xc0 + ((c & 0x0fc0) >> decalage);
	else if (size == 1)
		ch = c;
	size--;
	decalage -= 6;
	ft_fill_out(output, &ch, 1);
	while (size >= 1)
	{
		ft_bit_mask(decalage, c, &ch, size);
		ft_fill_out(output, &ch, 1);
		size--;
		decalage -= 6;
	}
}

void			ft_print_wide(t_out *tmp, t_arg *ele, wchar_t **ls, int *put)
{
	int			decalage;
	int			size;

	size = ft_widesize(**ls);
	*put += size;
	if (ele->type == 'C' || (ele->type == 'S' && (ele->precision < 1
					|| *put <= ele->precision)))
	{
		decalage = 6 * (size - 1);
		ft_putwide(tmp, **ls, size, decalage);
	}
	ele->len -= 1;
	*ls += 1;
}

void			ft_wide(t_out *output, t_out *tmp, t_arg *ele)
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
			ft_fill_out(tmp, "(null)", 6);
	}
	while (ele->len > 0 && (ele->type == 'C' || (ele->type == 'S'
					&& (ele->precision < 1 || put < ele->precision))))
		ft_print_wide(tmp, ele, &ls, &put);
	if (ele->type == 'S' && ele->precision == -1)
		ft_free_out(tmp);
	if (ele->pad != 0)
		ft_pad(tmp, 0, ele);
	ft_fill_out(output, tmp->out, tmp->len);
}
