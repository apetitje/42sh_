/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_typed_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:55:28 by oyagci            #+#    #+#             */
/*   Updated: 2017/06/26 16:05:46 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char			*get_typed_line(char *line, int start_index)
{
	char	*s;

	if (!(s = ft_strndup(line, start_index)))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	return (s);
}
