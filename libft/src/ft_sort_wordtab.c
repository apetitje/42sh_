/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_wordtab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 20:03:00 by apetitje          #+#    #+#             */
/*   Updated: 2017/05/05 16:48:39 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_sort_wordtab(char **tabl)
{
	int		is_sorting;
	char	**t;
	char	*swap;

	is_sorting = 1;
	while (is_sorting)
	{
		t = tabl;
		is_sorting = 0;
		while (*t && *(t + 1))
		{
			if (ft_strcmp(*t, *(t + 1)) > 0)
			{
				is_sorting = 1;
				swap = *t;
				*t = *(t + 1);
				*(t + 1) = swap;
			}
			++t;
		}
	}
}
