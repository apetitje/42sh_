/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 14:33:09 by oyagci            #+#    #+#             */
/*   Updated: 2017/08/22 13:02:16 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

enum e_modifier		get_mod_type(char c)
{
	enum e_modifier	type;

	type = 0;
	c == 'h' ? (type = MOD_REMOVE_TRAILING_PATHNAME_COMPONENT) : 0;
	c == 't' ? (type = MOD_REMOVE_ALL_LEADING_PATHNAME_COMPONENT) : 0;
	c == 'r' ? (type = MOD_REMOVE_SUFFIX) : 0;
	c == 'e' ? (type = MOD_REMOVE_ALL_BUT_TRAILING_SUFFIX) : 0;
	c == 'p' ? (type = MOD_PRINT) : 0;
	c == 'q' ? (type = MOD_QUOTE_WORDS) : 0;
	c == 'x' ? (type = MOD_SPLIT_AND_QUOTE) : 0;
	c == 's' ? (type = MOD_SUBSTITUTE) : 0;
	c == '&' ? (type = MOD_REPEAT) : 0;
	c == 'g' ? (type = MOD_GLOBAL) : 0;
	return (type);
}

t_modifier			*modifier_single(char *input, int *index)
{
	t_modifier	*mod;
	int			save;

	save = *index;
	if (input[*index] == ':')
		*index += 1;
	if (!(mod = ft_memalloc(sizeof(t_modifier))))
		exit_prog(EXIT_FAILURE, "Malloc error (modifier_single)\n");
	mod->type = get_mod_type(input[*index]);
	*index += 1;
	if (mod->type == MOD_GLOBAL)
		mod->type |= get_mod_type(input[*index]);
	mod->type & MOD_REPEAT ? *index += 1 : 0;
	if (mod->type & MOD_SUBSTITUTE)
		mod->sub = substitute(input, index);
	if (mod->type == 0)
	{
		free(mod);
		mod = NULL;
		*index = save;
	}
	return (mod);
}

t_list				*modifier(char *input, int *index)
{
	t_list		*elem;
	t_list		*mlst;
	t_modifier	*mod;

	mlst = NULL;
	while ((mod = modifier_single(input, index)))
	{
		elem = ft_lstnew(mod, sizeof(*mod));
		ft_lstaddback(&mlst, elem);
	}
	return (mlst);
}
