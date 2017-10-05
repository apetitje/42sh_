/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pad.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 19:43:10 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 16:41:33 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_find_pad(t_arg *ele, int i, const char *str)
{
	ele->pad = ft_atoi(str + i);
	while (str[i] && ft_isdigit(str[i]))
		++i;
	--i;
	return (i);
}

static int		ft_padright(t_arg *ele, char *flag, t_out *output)
{
	int		i;
	char	*ptr;
	int		len;

	i = -1;
	ptr = NULL;
	if (flag && *flag)
	{
		while (++i < ele->pad)
			ft_join_before(output, &(ele->padchar), 1);
		ft_join_before(output, flag, ft_strlen(flag));
	}
	else if (ele->pad > 0 && output->len > 0 && ft_strchr("dDifF", ele->type)
			&& *(output->out) == '-' && ele->padchar == '0')
	{
		ptr = ft_strndup(output->out + 1, output->len - 1);
		len = output->len - 1;
		ft_free_out(output);
		ft_fill_out(output, "-", 1);
		while (++i < ele->pad)
			ft_fill_out(output, &(ele->padchar), 1);
		ft_fill_out(output, ptr, len);
		free(ptr);
	}
	return (i);
}

void			ft_pad(t_out *output, char *flag, t_arg *ele)
{
	int		i;

	i = -1;
	if (ele->padleft != 1)
		ele->padleft = (ele->pad < 0) ? 1 : 0;
	ele->pad = ((ele->pad < 0) ? -(ele->pad) : ele->pad) - output->len;
	if (ele->padleft == 1)
	{
		if (flag && *flag)
			ft_join_before(output, flag, ft_strlen(flag));
		while (++i < ele->pad)
			ft_fill_out(output, &(ele->padchar), 1);
	}
	else
	{
		if ((ele->padchar == ' ' || ele->type == 'Z') && flag && *flag)
			ft_join_before(output, flag, ft_strlen(flag));
		else
			i = ft_padright(ele, flag, output);
	}
	while (++i < ele->pad)
		ft_join_before(output, &(ele->padchar), 1);
}
