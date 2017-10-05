/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_by_index.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 12:25:46 by oyagci            #+#    #+#             */
/*   Updated: 2017/06/29 12:29:48 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int				is_number(char *s)
{
	if (ft_isdigit(*s) || (*s == '-' && ft_isdigit(*(s + 1))))
		return (1);
	return (0);
}

char			*get_command_from_top(int index)
{
	t_list	*hist;
	int		i;
	char	*s;

	i = 1;
	hist = g_hist;
	while (hist && hist->next)
		hist = hist->next;
	while (hist && hist->prev && i < index)
	{
		i += 1;
		hist = hist->prev;
	}
	if (i == index)
	{
		if (!(s = ft_strdup(get_hist(hist))))
			exit_prog(EXIT_FAILURE, "Malloc error (get_cmd_form_top)\n");
		return (s);
	}
	return (NULL);
}

char			*get_command_from_bot(int index)
{
	t_list	*hist;
	int		i;
	char	*s;

	i = 1;
	hist = g_hist;
	while (i < index && hist && hist->next)
	{
		hist = hist->next;
		i += 1;
	}
	if (i == index)
	{
		if (!(s = ft_strdup(get_hist(hist))))
			exit_prog(EXIT_FAILURE, "Malloc error (get_cmd_from_bot)\n");
		return (s);
	}
	return (NULL);
}

char			*get_command_by_index(int index)
{
	t_list	*hist;
	int		i;

	i = 0;
	hist = g_hist;
	if (index > 0)
		return (get_command_from_top(index));
	else if (index < 0)
		return (get_command_from_bot(-index));
	return (NULL);
}
