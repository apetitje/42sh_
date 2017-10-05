/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 12:00:12 by clabouri          #+#    #+#             */
/*   Updated: 2017/06/16 08:54:47 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strcat(char *s1, const char *s2)
{
	char *t_s;

	t_s = s1 + ft_strlen(s1);
	ft_strcpy(t_s, s2);
	return (s1);
}
