/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 20:04:14 by apetitje          #+#    #+#             */
/*   Updated: 2016/08/08 00:32:56 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_sqrt(int nb)
{
	int		sqrt;

	sqrt = 1;
	if (nb <= 0)
		return (0);
	while (nb >= sqrt && sqrt < 46341)
	{
		if (nb % sqrt == 0 && nb / sqrt == sqrt)
			return (sqrt);
		else
			sqrt++;
	}
	return (0);
}
