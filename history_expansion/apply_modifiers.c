/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_modifiers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 15:42:42 by oyagci            #+#    #+#             */
/*   Updated: 2017/08/22 14:02:36 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int				apply_modifier(t_modifier *mod, char **event)
{
	if (mod->type == MOD_REMOVE_TRAILING_PATHNAME_COMPONENT)
		rm_trailing_pathname_component(event);
	else if (mod->type == MOD_REMOVE_ALL_LEADING_PATHNAME_COMPONENT)
		rm_all_leading_pathname_component(event);
	else if (mod->type == MOD_REMOVE_SUFFIX)
		rm_suffix(event);
	else if (mod->type == MOD_REMOVE_ALL_BUT_TRAILING_SUFFIX)
		rm_all_but_trailing_suffix(event);
	else if (mod->type & MOD_SUBSTITUTE)
		apply_substitute(mod->sub, event, mod->type & MOD_GLOBAL);
	else if (mod->type == MOD_QUOTE_WORDS)
		quote_words(event);
	else if (mod->type == MOD_SPLIT_AND_QUOTE)
		quote_split(event);
	else if (mod->type & MOD_REPEAT)
		repeat_sub(event, mod->type & MOD_GLOBAL);
	else if (mod->type == MOD_PRINT)
		return (1);
	return (0);
}

void			add_to_hist(char *str)
{
	t_i_line	l;

	l.input.data = str;
	stock_hist(&l, &g_hist);
}

int				apply_modifiers(t_list *modifiers, char **event)
{
	int	print;

	print = 0;
	while (modifiers)
	{
		print |= apply_modifier(modifiers->data, event);
		modifiers = modifiers->next;
	}
	if (print)
	{
		ft_printf("%s", *event);
		add_to_hist(*event);
		ft_strclr(*event);
	}
	return (1);
}
