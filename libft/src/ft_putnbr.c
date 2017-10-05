/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:57:32 by apetitje          #+#    #+#             */
/*   Updated: 2016/11/05 19:13:44 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(int n)
{
	unsigned int	absolute_nb;
	char			number[10];
	int				range;

	range = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		absolute_nb = (unsigned int)-n;
	}
	else
		absolute_nb = (unsigned int)n;
	while (absolute_nb >= 10)
	{
		number[range] = absolute_nb % 10 + 48;
		absolute_nb = absolute_nb / 10;
		range++;
	}
	number[range] = absolute_nb + 48;
	while (range >= 0)
	{
		write(1, &(number[range]), 1);
		range--;
	}
}
