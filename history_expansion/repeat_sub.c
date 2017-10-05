/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 11:51:03 by oyagci            #+#    #+#             */
/*   Updated: 2017/08/22 12:28:41 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void			repeat_sub(char **event, int global)
{
	if (!g_prev_sub)
	{
		ft_printf("no previous substitution");
		ft_strclr(*event);
		return ;
	}
	else
		apply_substitute(g_prev_sub, event, global);
}
