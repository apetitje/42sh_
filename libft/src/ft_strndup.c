/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 12:00:28 by clabouri          #+#    #+#             */
/*   Updated: 2017/06/16 08:56:00 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*ret;
	size_t	len;

	len = ft_strlen(s);
	len = (len <= n) ? len : n;
	return ((ret = ft_strnew(len)) ? ft_strncpy(ret, s, n) : NULL);
}
