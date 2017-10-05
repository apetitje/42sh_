/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 19:24:37 by apetitje          #+#    #+#             */
/*   Updated: 2016/11/06 15:30:56 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	absolute_nb;
	char			number[10];
	int				range;

	if (fd != -1)
	{
		range = 0;
		if (n < 0)
		{
			write(fd, "-", 1);
			absolute_nb = (unsigned int)-n;
		}
		else
			absolute_nb = (unsigned int)n;
		while (absolute_nb >= 10)
		{
			number[range++] = absolute_nb % 10 + 48;
			absolute_nb = absolute_nb / 10;
		}
		number[range] = absolute_nb + 48;
		while (range >= 0)
			write(fd, &(number[range--]), 1);
	}
}
