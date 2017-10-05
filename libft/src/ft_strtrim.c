/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 18:45:04 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/27 12:23:00 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static int	ft_new_len(int *ind, int *end, char const *s)
{
	int	new_len;

	*ind = 0;
	while (s[*ind] && (s[*ind] == ' ' || s[*ind] == '\n' || s[*ind] == '\t'))
		(*ind)++;
	while (s[*end] && (s[*end] == ' ' || s[*end] == '\n' || s[*end] == '\t'))
		(*end)--;
	new_len = *end - *ind + 1;
	(*ind)--;
	if (new_len < 0)
		new_len = 0;
	return (new_len);
}

char		*ft_strtrim(char const *s)
{
	int		ind;
	int		len;
	int		end;
	int		new_len;
	char	*trimed_s;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	end = len - 1;
	new_len = ft_new_len(&ind, &end, s);
	if (new_len == len)
		trimed_s = ft_strdup(s);
	else
	{
		if (!(trimed_s = (char *)malloc(sizeof(char) * (new_len + 1))))
			return (NULL);
		len = 0;
		while (++ind < end + 1)
			trimed_s[len++] = s[ind];
		trimed_s[len] = '\0';
	}
	return (trimed_s);
}
