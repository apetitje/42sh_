/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 13:43:12 by oyagci            #+#    #+#             */
/*   Updated: 2017/06/30 13:47:32 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int				insert_event(char **line, char *event, int start, int end)
{
	size_t	l;
	char	*new;

	l = ft_strlen(event);
	if (!(new = ft_strnew(ft_strlen(*line) + l)))
		exit_prog(EXIT_FAILURE, "Malloc error (inset_event)\n");
	ft_strncpy(new, *line, start);
	ft_strcat(new, event);
	ft_strcat(new, *line + end);
	if (ft_strlen(new) < SIZE - 1)
		ft_strcpy(*line, new);
	else
	{
		ft_dprintf(2, "Resulting line too big\n");
		ft_strclr(*line);
		return (0);
	}
	free(new);
	return (1);
}

int				apply_expansion(t_expansion *e, char **line)
{
	char	*event;

	if ((event = get_event(e->event_designator, *line, e->start_index)))
	{
		if (apply_word(e->word_designator, &event)
				&& apply_modifiers(e->modifiers, &event))
		{
			if (!insert_event(line, event, e->start_index, e->end_index))
			{
				free(event);
				return (0);
			}
		}
		else
		{
			free(event);
			return (0);
		}
		free(event);
		return (1);
	}
	else
		ft_printf("Event not found\n");
	return (0);
}
