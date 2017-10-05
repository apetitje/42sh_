/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_designator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 12:25:06 by oyagci            #+#    #+#             */
/*   Updated: 2017/06/21 16:36:25 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int					set_arg_nb(t_arg_designator *arg, char *input, int *index)
{
	if (ft_isdigit(input[*index]))
	{
		arg->number = ft_atoi(input + *index);
		while (ft_isdigit(input[*index]))
			*index += 1;
		return (1);
	}
	return (0);
}

t_arg_designator	*arg_designator(char *input, int *index)
{
	t_arg_designator	*arg;
	int					save;

	save = *index;
	if (!(arg = ft_memalloc(sizeof(t_arg_designator))))
		exit_prog(EXIT_FAILURE, "Malloc error (arg_designator)\n");
	if (input[*index] == '$')
	{
		arg->type = AD_LAST;
		*index += 1;
	}
	else if (input[*index] == '^')
	{
		arg->type = AD_FIRST;
		*index += 1;
	}
	else if (!set_arg_nb(arg, input, index))
	{
		free(arg);
		arg = NULL;
		*index = save;
	}
	return (arg);
}
