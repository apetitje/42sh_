/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 14:36:03 by oyagci            #+#    #+#             */
/*   Updated: 2017/09/27 10:06:46 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int				print_history(void)
{
	t_list	*hist;
	int		i;

	i = 1;
	hist = g_hist;
	while (hist && hist->next)
		hist = hist->next;
	while (hist)
	{
		ft_printf("%6d  %s\n", i++, get_hist(hist));
		hist = hist->prev;
	}
	return (0);
}
