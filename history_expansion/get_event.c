/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 10:19:26 by oyagci            #+#    #+#             */
/*   Updated: 2017/06/27 17:16:42 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

char			*get_prev_line(void)
{
	t_list	*hist;

	hist = g_hist;
	if (hist)
		return (ft_strdup(get_hist(hist)));
	return (NULL);
}

char			*get_hist_line(t_expansion *e)
{
	if (e->event_designator && e->event_designator->type == ED_PREVIOUS)
		return (get_prev_line());
	return (NULL);
}

char			*get_command_string(char *s)
{
	t_list	*hist;
	char	*line;
	int		nb;

	if (is_number(s))
	{
		nb = ft_atoi(s);
		return (get_command_by_index(nb));
	}
	else
	{
		hist = g_hist;
		while (hist)
		{
			if (ft_strncmp(get_hist(hist), s, ft_strlen(s)) == 0)
			{
				if (!(line = ft_strdup(get_hist(hist))))
					exit_prog(EXIT_FAILURE, "Malloc error\n");
				return (line);
			}
			hist = hist->next;
		}
	}
	return (NULL);
}

char			*get_command_keyword(char *s)
{
	t_list	*hist;
	char	*line;

	hist = g_hist;
	while (hist)
	{
		if (ft_strstr(get_hist(hist), s))
		{
			if (!(line = ft_strdup(get_hist(hist))))
				exit_prog(EXIT_FAILURE, "Malloc error (get_cmd_keyword)\n");
			return (line);
		}
		hist = hist->next;
	}
	return (NULL);
}

char			*get_event(t_event_designator *e, char *line, int start_index)
{
	char	*event;

	event = NULL;
	if (!e)
		return (NULL);
	if (e->type == ED_PREVIOUS)
		event = get_prev_line();
	else if (e->type == ED_STRING)
		event = get_command_string(e->data);
	else if (e->type == ED_KEYWORD)
		event = get_command_keyword(e->data);
	else if (e->type == ED_LINE)
		event = get_typed_line(line, start_index);
	return (event);
}
