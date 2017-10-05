/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 12:32:37 by oyagci            #+#    #+#             */
/*   Updated: 2017/09/28 10:24:57 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_expansion		*get_expansion(char *input, int *index)
{
	t_expansion	*e;

	if (!(e = ft_memalloc(sizeof(t_expansion))))
		exit_prog(EXIT_FAILURE, "Malloc error (get_expansion)\n");
	e->start_index = *index - 1;
	if ((e->event_designator = event_designator(input, index)))
	{
		if (input[*index] == ':')
		{
			*index += 1;
			e->word_designator = word_designator(input, index);
			e->modifiers = modifier(input, index);
		}
		e->end_index = *index;
	}
	else
	{
		free(e);
		e = NULL;
	}
	return (e);
}

void			free_expansion(t_expansion *e)
{
	free_event_designator(e->event_designator);
	free_word_designator(e->word_designator);
	free_modifiers(e->modifiers);
	free(e);
}

int				do_expansion(char *line, int *index)
{
	t_expansion	*e;

	if ((e = get_expansion(line, index)))
	{
		if (!(apply_expansion(e, &line)))
		{
			free_expansion(e);
			return (0);
		}
		free_expansion(e);
	}
	else
		return (2);
	return (1);
}

void			ign_quote(char *line, int *i)
{
	if (line[*i] == '\'')
	{
		if (!(*i > 0 && line[*i - 1] == '\\'))
		{
			*i += 1;
			while (1)
			{
				if (0 == line[*i] || line[*i] == '\'')
					break ;
				*i += 1;
			}
		}
	}
}

char			*history_expansion(char *line)
{
	int			i;
	int			expanded;
	int			ret;

	expanded = 0;
	i = 0;
	while (line[i] != 0)
	{
		ign_quote(line, &i);
		line[i] == '^' ? quick_sub(line, &i) : 0;
		if (line[i++] == '!')
		{
			if (check_ifglob(line, line + i - 1))
				continue ;
			if (0 == (ret = do_expansion(line, &i)))
			{
				ft_strclr(line);
				break ;
			}
			else if (ret != 2)
				expanded += 1;
		}
	}
	expanded ? ft_printf("%s\n", line) : 0;
	return (line);
}
