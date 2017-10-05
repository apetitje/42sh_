/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_word_designator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 17:06:35 by oyagci            #+#    #+#             */
/*   Updated: 2017/06/21 17:35:02 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			free_word_designator(t_word_designator *wd)
{
	if (wd)
	{
		free_range_designator(wd->range);
		free(wd);
	}
}
