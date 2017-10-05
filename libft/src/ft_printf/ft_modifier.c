/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 12:18:32 by apetitje          #+#    #+#             */
/*   Updated: 2017/01/07 20:38:06 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_find_type2(t_arg *ele, const char *str, int i)
{
	if (str[i] == 'h')
	{
		if (!ft_strchr("jzlL", ele->modifier))
		{
			ele->modifier = str[i];
			if (str[i - 1] && str[i - 1] == 'h')
				ele->modifier = 'H';
		}
	}
	else if (ft_strchr("lzj", str[i]))
	{
		ele->modifier = str[i];
		if (str[i] == 'l' && ((str[i - 1] && str[i - 1] == 'l')))
			ele->modifier = 'L';
	}
	else if (str[i] == '#')
		ele->hash = 1;
	else if (str[i] == '+')
		ele->plus = 1;
	else if (str[i] == '-')
		ele->padleft = 1;
	else if (str[i] == '0')
		if (i == 0 || ft_isdigit(str[i - 1]) == 0)
			ele->zero = 1;
}

static int	ft_find_type(const char *str, t_arg *ele, va_list ap)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (ft_strchr("hlzj0#+-", str[i]))
			ft_find_type2(ele, str, i);
		else if (str[i] == ' ')
			ele->space = 1;
		else if (str[i] == '*')
			ft_wild(str, i, ele, ap);
		else if (ft_isdigit(str[i]) && (i == 0 || str[i - 1] != '.'))
			i = ft_find_pad(ele, i, str);
		else if (str[i] == '.' && str + i + 1)
			i = ft_precision(ele, i, str);
		else
		{
			ele->type = str[i];
			return (i);
		}
	}
	ele->type = str[i];
	return (i);
}

t_arg		*ft_find_modif(const char **str, va_list ap)
{
	t_arg	*ele;
	int		i;

	*str += 1;
	ele = ft_arg();
	i = ft_find_type(*str, ele, ap);
	*str = *str + i;
	if (ele->type == '\0')
	{
		free(ele);
		return (NULL);
	}
	if (ft_strchr("uoxXb", ele->type))
		ele->unsign = 1;
	ele->format = ele->type;
	ft_modifier(ele);
	if (ele->zero && (((ft_strchr("scSC%Z", ele->type) || ele->precision == 0)
					&& !ele->padleft) || (ele->precision != 0 && ele->wild)))
		ele->padchar = '0';
	return (ele);
}

static void	ft_num_modif(t_arg *ele)
{
	if (ele->modifier == 'z')
	{
		if (ele->unsign)
			ele->format = 'U';
		else if (ele->type == 'd' || ele->type == 'i')
			ele->type = 'L';
	}
	else if (ele->modifier == 'H')
	{
		if (ele->unsign)
			ele->format = 'w';
		else if (ele->type == 'd' || ele->type == 'i')
			ele->type = 'z';
	}
	else if (ele->modifier == 'h')
	{
		if (ele->unsign)
			ele->format = 'y';
		else if (ele->type == 'd' || ele->type == 'i')
			ele->format = 'h';
	}
}

void		ft_modifier(t_arg *ele)
{
	if (ele->modifier == 'l')
	{
		if (ele->unsign)
			ele->format = 'U';
		else if (ele->type == 'd' || ele->type == 'i')
			ele->type = 'D';
		else if (ele->type == 's' || ele->type == 'c')
		{
			ele->type = (ele->type == 's') ? 'S' : 'C';
			ele->format = (ele->type == 'C') ? 'C' : ele->format;
		}
	}
	else if (ele->modifier == 'L')
	{
		if (ele->unsign)
			ele->format = 'K';
		else if (ele->type == 'd' || ele->type == 'i')
			ele->type = 'L';
	}
	else if (ele->modifier == 'j' && (ele->type == 'd' || ele->type == 'i'))
		ele->type = 'D';
	else if (ele->modifier == 'j' && ele->unsign)
		ele->format = 'U';
	ft_num_modif(ele);
}
