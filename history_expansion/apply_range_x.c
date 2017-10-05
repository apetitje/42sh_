/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_range_x.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 13:28:11 by oyagci            #+#    #+#             */
/*   Updated: 2017/06/26 16:26:06 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int				apply_range_x(t_range_designator *r, char **event)
{
	char	**words;
	int		low;

	if (!(words = ft_strsplit(*event, ' ')))
		exit_prog(EXIT_FAILURE, "Malloc error (apply_range_x)\n");
	low = 1;
	if (r->left)
		low = get_index(r->left, words);
	if (low > nb_words(words))
	{
		ft_printf("Bad range\n");
		ft_tabfree(words);
		return (0);
	}
	if (!(set_range(low, nb_words(words) - 1, event, words)))
	{
		ft_tabfree(words);
		return (0);
	}
	ft_tabfree(words);
	return (1);
}
