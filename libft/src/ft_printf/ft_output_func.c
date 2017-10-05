/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 18:32:31 by apetitje          #+#    #+#             */
/*   Updated: 2017/02/10 14:08:21 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_fill_out(t_out *out, const char *format, int len)
{
	if (len > 0 && format)
	{
		if (out->len + len <= BUFFSIZE)
			ft_memcpy(out->out + out->len, format, len);
		else
		{
			if (out->stocked)
			{
				if (!(out->out = ft_realloc(out->out, 1 + len + out->len,
								out->len)))
					exit(EXIT_FAILURE);
			}
			else
			{
				if (!(out->out = (char *)malloc(sizeof(char)
								* (out->len + len + 1))))
					exit(EXIT_FAILURE);
				out->out = ft_memcpy(out->out, out->out1, out->len);
			}
			ft_memcpy(out->out + out->len, format, len);
			out->stocked = 1;
		}
	}
	out->len += len;
}

void	ft_join_before(t_out *out, const char *s, int len)
{
	char	*new_str;
	int		nlen;

	if (len > 0)
	{
		if (!s)
			return ;
		else
		{
			if (!(new_str = (char *)malloc(sizeof(char)
							* (out->len + len + 1))))
				exit(EXIT_FAILURE);
			new_str = ft_memcpy(new_str, s, len);
			ft_memcpy(new_str + len, out->out, out->len);
			nlen = out->len + len;
			ft_free_out(out);
			ft_fill_out(out, new_str, nlen);
			free(new_str);
		}
	}
}
