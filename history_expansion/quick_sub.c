/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 10:46:00 by oyagci            #+#    #+#             */
/*   Updated: 2017/10/03 16:26:21 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			get_quick_left_right(char **left, char **right, char *input, int *i)
{
	int		end;

	*right = 0;
	*left = ft_strchr(input + *i + 1, '^');
	if (*left)
		*right = ft_strchr(*left + 1, '^');
	if (*right)
	{
		end = *right - input;
		if (!(*right = ft_strndup(*left + 1, *right - (*left + 1)))
			|| !(*left = ft_strndup(input + *i + 1, *left - (input + *i + 1))))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		*i = end;
		return (1);
	}
	return (0);
}

int			quick_replace_word(char **str, char *input, int *index)
{
	char	*left;
	char	*right;
	char	*word;
	char	*new;

	if (!get_quick_left_right(&left, &right, input, index))
		return (0);
	if (NULL != (word = ft_strstr(*str, left)))
	{
		if (!(new = ft_strnew((
				ft_strlen(*str) + ft_strlen(right)) - ft_strlen(left))))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		ft_strncpy(new, *str, word - *str);
		ft_strcat(new, right);
		ft_strcat(new, word + ft_strlen(left));
		free(*str);
		*str = new;
	}
	free(left);
	free(right);
	return (1);
}

int			quick_sub(char *line, int *index)
{
	char				*string;
	t_event_designator	*event;

	if (NULL == (event = ft_memalloc(sizeof(t_event_designator))))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	event->type = ED_PREVIOUS;
	string = get_prev_line();
	if (!quick_replace_word(&string, line, index))
		*index += 1;
	else if (ft_strlen(string) < SIZE - 1)
	{
		ft_strcpy(line, string);
	}
	free(string);
	free(event);
	return (0);
}
