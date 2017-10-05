/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 12:00:12 by clabouri          #+#    #+#             */
/*   Updated: 2017/06/16 08:55:40 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*t_s;

	t_s = s1 + ft_strlen(s1);
	ft_strncpy(t_s, s2, n);
	return (s1);
}
