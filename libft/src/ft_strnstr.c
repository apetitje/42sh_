/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:59:38 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/27 12:19:31 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		little_len;

	if (!*little)
		return ((char *)big);
	little_len = ft_strlen(little);
	while (len && *big)
	{
		if (little_len > len)
			return (NULL);
		if (*big == *little)
			if (ft_strncmp(big, little, little_len) == 0)
				return ((char *)big);
		len--;
		big++;
	}
	return (NULL);
}
