/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_range.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 10:21:22 by oyagci            #+#    #+#             */
/*   Updated: 2017/06/26 16:42:23 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int				get_index(t_arg_designator *arg, char **words)
{
	int		i;

	i = 0;
	if (arg->type == AD_FIRST)
		return (1);
	if (arg->type == AD_LAST)
	{
		while (words[i] && words[i + 1])
			i += 1;
		return (i);
	}
	else if (arg->type == AD_NUMBER)
		return (arg->number);
	return (-1);
}

void			set_ranged_event(char **event, char **ranged)
{
	int		i;

	i = 0;
	ft_strclr(*event);
	while (ranged[i] != 0)
	{
		ft_strcat(*event, ranged[i]);
		if (ranged[i + 1] != 0)
			ft_strcat(*event, " ");
		i += 1;
	}
}

int				set_range(int low, int high, char **event, char **words)
{
	int		i;
	char	**ranged;

	if (!(ranged = ft_memalloc(sizeof(char *) * (((high + 1) - low) + 1))))
		exit_prog(EXIT_FAILURE, "Malloc error (set_range)\n");
	i = low;
	if (nb_words(words) >= low)
		while (i <= high && words[i])
		{
			if (!(ranged[i - low] = ft_strdup(words[i])))
				exit_prog(EXIT_FAILURE, "Malloc error (set_range 2)\n");
			i += 1;
		}
	if (i <= high)
	{
		ft_dprintf(2, "Bad range\n", low, high);
		ft_tabfree(ranged);
		return (0);
	}
	set_ranged_event(event, ranged);
	ft_tabfree(ranged);
	return (1);
}

int				apply_range_xy(t_range_designator *r, char **event)
{
	char	**words;
	int		low;
	int		high;

	if (!(words = ft_strsplit(*event, ' ')))
		exit_prog(EXIT_FAILURE, "Malloc error (apply_range_xy");
	low = 0;
	if (r->left)
		low = get_index(r->left, words);
	high = low;
	if (r->right)
		high = get_index(r->right, words);
	if (low > high)
	{
		ft_dprintf(2, "Bad range\n");
		ft_tabfree(words);
		return (0);
	}
	if (!(set_range(low, high, event, words)))
	{
		ft_tabfree(words);
		return (0);
	}
	ft_tabfree(words);
	return (1);
}

int				apply_range(t_range_designator *r, char **event)
{
	if (r)
	{
		if (r->type == R_RANGE)
			return (apply_range_xy(r, event));
		else if (r->type == R_X_RANGE)
			return (apply_range_x(r, event));
	}
	return (0);
}
