/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_designator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 10:45:48 by oyagci            #+#    #+#             */
/*   Updated: 2017/06/29 12:17:27 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "history_expansion.h"

int					set_string(t_event_designator *event, char *input,
		int *index)
{
	int		i;

	i = *index;
	if (ft_isdigit(input[i]) && input[i] != '0')
		while (input[i] && input[i] != ':' && ft_isdigit(input[i]))
			i += 1;
	else
		while (input[i] && input[i] != ':' && !ft_isspace(input[i]))
			i += 1;
	if (i - *index > 0)
	{
		if (!(event->data = ft_strndup(input + *index, i - 1)))
			exit_prog(EXIT_FAILURE, "Malloc error (set_event_string)\n");
		*index = i;
		return (1);
	}
	return (0);
}

int					set_keyword(t_event_designator *event, char *input,
		int *index)
{
	int	i;
	int	end;
	int	start;

	end = 0;
	i = *index;
	while (input[i] && input[i] != '?')
	{
		i += 1;
		end += 1;
		if (input[i] == '?')
			break ;
	}
	start = *index;
	if (end > 0)
	{
		if (!(event->data = ft_strndup(input + *index, end)))
			exit_prog(EXIT_FAILURE, "Malloc error (set_event_string)\n");
		*index += i;
		return (1);
	}
	return (0);
}

int					set_event_string(t_event_designator *event, char *input,
		int *index)
{
	event->type = ED_STRING;
	if (input[*index] == '?')
	{
		event->type = ED_KEYWORD;
		*index += 1;
	}
	if (event->type == ED_KEYWORD)
		return (set_keyword(event, input, index));
	else
		return (set_string(event, input, index));
}

t_event_designator	*event_designator(char *input, int *index)
{
	int					save;
	t_event_designator	*event;

	save = *index;
	if (!(event = ft_memalloc(sizeof(t_event_designator))))
		exit_prog(EXIT_FAILURE, "Malloc error (event_designator)\n");
	event->type = ED_PREVIOUS;
	if (input[*index] == '!')
		*index += 1;
	else if (input[*index] == '#')
	{
		event->type = ED_LINE;
		*index += 1;
	}
	else if (!set_event_string(event, input, index))
	{
		*index = save;
		free(event);
		event = NULL;
	}
	return (event);
}
