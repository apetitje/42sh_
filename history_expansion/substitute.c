/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sed.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 12:45:56 by oyagci            #+#    #+#             */
/*   Updated: 2017/07/11 13:11:06 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int				set_left_right(t_sub *s, char *input, int *index)
{
	int	i;

	i = *index;
	if (input[*index] != '/')
		return (0);
	*index += 1;
	i = *index;
	while (input[*index] && input[*index] != '/')
		*index += 1;
	if (input[*index] != '/')
		return (0);
	if (!(s->left = ft_strndup(input + i, *index - i)))
		exit_prog(EXIT_FAILURE, "Malloc error (set_left_right)\n");
	*index += 1;
	i = *index;
	while (input[*index] && input[*index] != '/')
		*index += 1;
	if (!(s->right = ft_strndup(input + i, *index - i)))
		exit_prog(EXIT_FAILURE, "Malloc error (set_left_right)\n");
	(input[*index] == '/') ? *index += 1 : 0;
	return (1);
}

t_sub			*substitute(char *input, int *index)
{
	t_sub	*sub;
	int		save;

	if (!(sub = ft_memalloc(sizeof(t_sub))))
		exit_prog(EXIT_FAILURE, "Malloc error (substitute)\n");
	save = *index;
	if (input[*index] == 's')
		*index += 1;
	if (set_left_right(sub, input, index) == 0)
	{
		free(sub);
		*index = save;
		return (NULL);
	}
	return (sub);
}
