/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 02:10:29 by clabouri          #+#    #+#             */
/*   Updated: 2016/11/06 03:10:35 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strrev(char *s)
{
	int		i;
	int		j;
	char	tmp;

	i = -1;
	j = ft_strlen(s);
	while (++i < --j)
	{
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
	}
	return (s);
}