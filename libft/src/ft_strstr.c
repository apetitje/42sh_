/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:50:04 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/27 12:19:17 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strstr(const char *big, const char *little)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (little[j] == '\0')
		return ((char *)big);
	while (big[i] != '\0')
	{
		while (big[i] && big[i] != little[j])
			i++;
		if (big[i] == little[j--])
		{
			while (little[++j] && big[i] == little[j])
				i++;
			if (little[j] == '\0')
				return ((char *)big + i - j);
			else
			{
				i = i - j + 1;
				j = 0;
			}
		}
	}
	return (NULL);
}
