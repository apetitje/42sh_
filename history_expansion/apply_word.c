/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 11:31:27 by oyagci            #+#    #+#             */
/*   Updated: 2017/06/26 13:29:09 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int				apply_last_matched(char **event)
{
	(void)event;
	return (0);
}

int				apply_word(t_word_designator *e, char **event)
{
	if (!e)
		return (1);
	if (e->type == WD_RANGE)
		return (apply_range(e->range, event));
	else if (e->type == WD_LAST_MATCHED)
		return (apply_last_matched(event));
	return (0);
}
