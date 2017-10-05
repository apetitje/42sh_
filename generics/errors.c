/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 18:24:34 by apetitje          #+#    #+#             */
/*   Updated: 2017/09/29 13:40:02 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int		error_and_return(char *msg)
{
	if (msg)
		ft_dprintf(2, "42sh: %s\n", msg);
	g_exit_status = 1;
	return (1);
}

char	*error_in_waiting(char **sequence)
{
	if ((sequence && *sequence))
	{
		ft_memdel((void **)sequence);
		ft_dprintf(2, "42sh: syntax error: unexpected EOF\n");
	}
	else if ((!sequence || !*sequence) && !g_interactive)
		ft_dprintf(2, "42sh: syntax error: unexpected EOF\n");
	g_prompt_size = 3;
	g_exit_status = 1;
	return (NULL);
}
