/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 19:22:54 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/27 12:22:18 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void	ft_putendl_fd(char const *s, int fd)
{
	if (s && fd != -1)
	{
		ft_putstr_fd(s, fd);
		write(fd, "\n", 1);
	}
}
