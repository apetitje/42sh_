/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 12:50:55 by oyagci            #+#    #+#             */
/*   Updated: 2017/10/03 16:26:05 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "history_expansion.h"

t_arg_designator	*range_arg_designator_left(char *input, int *index)
{
	t_arg_designator	*d;

	d = arg_designator(input, index);
	if (!d && input[*index] == '-')
	{
		if (!(d = ft_memalloc(sizeof(t_arg_designator))))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		d->type = AD_NUMBER;
		d->number = 0;
	}
	return (d);
}

t_arg_designator	*range_arg_designator_right(char *input, int *index)
{
	t_arg_designator	*d;

	if (!(d = arg_designator(input, index)))
	{
		if (!(d = ft_memalloc(sizeof(t_arg_designator))))
			exit_prog(EXIT_FAILURE, "Malloc error (range_arg right)\n");
		d->type = AD_LAST;
	}
	return (d);
}

t_range_designator	*range_designator(char *input, int *index)
{
	t_range_designator	*range;
	int					save;

	save = *index;
	if (!(range = ft_memalloc(sizeof(t_range_designator))))
		exit_prog(EXIT_FAILURE, "Malloc error (range)\n");
	range->type = R_RANGE;
	range->left = range_arg_designator_left(input, index);
	if (input[*index] == '-')
	{
		*index += 1;
		range->right = range_arg_designator_right(input, index);
	}
	else if (input[*index] == '*')
	{
		range->type = R_X_RANGE;
		*index += 1;
	}
	if (!range->left && !range->right && range->type != R_X_RANGE)
	{
		free(range);
		range = NULL;
		*index = save;
	}
	return (range);
}
