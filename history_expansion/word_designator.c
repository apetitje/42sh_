/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_designator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 13:43:01 by oyagci            #+#    #+#             */
/*   Updated: 2017/06/21 14:16:46 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_word_designator	*word_designator(char *input, int *index)
{
	t_word_designator	*word;
	int					save;

	save = *index;
	if (!(word = ft_memalloc(sizeof(t_word_designator))))
		exit_prog(EXIT_FAILURE, "Malloc error (word_designator)\n");
	if ((word->range = range_designator(input, index)))
		word->type = WD_RANGE;
	else if (input[*index] == '%')
	{
		*index += 1;
		word->type = WD_LAST_MATCHED;
	}
	else
	{
		free(word);
		word = NULL;
		*index = save;
	}
	return (word);
}
