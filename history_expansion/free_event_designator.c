/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_event_designator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 17:03:35 by oyagci            #+#    #+#             */
/*   Updated: 2017/06/22 11:22:18 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			free_event_designator(t_event_designator *event)
{
	if (event)
	{
		free(event->data);
		free(event);
	}
}
