/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_range_designator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 17:08:16 by oyagci            #+#    #+#             */
/*   Updated: 2017/06/22 12:41:21 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			free_range_designator(t_range_designator *range)
{
	if (range)
	{
		free_arg_designator(range->left);
		free_arg_designator(range->right);
		free(range);
	}
}
