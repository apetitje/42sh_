/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_modifiers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 17:19:59 by oyagci            #+#    #+#             */
/*   Updated: 2017/06/22 13:29:48 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			free_modifiers(t_list *modifiers)
{
	t_list	*next;

	while (modifiers)
	{
		next = modifiers->next;
		free_substitute(((t_modifier *)modifiers->data)->sub);
		free(modifiers->data);
		free(modifiers);
		modifiers = next;
	}
}
