/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 01:06:01 by clabouri          #+#    #+#             */
/*   Updated: 2017/10/05 12:51:31 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strjoinf(void *s1, void *s2, int which)
{
	char *ret;

	ret = ft_strjoin(s1, s2);
	if (which == 1 || which == 3)
		ft_strdel((char**)&s1);
	if (which == 2 || which == 3)
		ft_strdel((char**)&s2);
	return (ret);
}

char	*ft_strjoinfree(char *s1, char *s2, int which)
{
	char *ret;

	ret = ft_strjoin(s1, s2);
	if (which == 1 || which == 3)
		ft_strdel(&s1);
	if (which == 2 || which == 3)
		ft_strdel(&s2);
	return (ret);
}
