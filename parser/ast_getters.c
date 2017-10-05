/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_getters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 13:29:25 by apetitje          #+#    #+#             */
/*   Updated: 2017/08/20 20:28:11 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_tok_type	get_tok_type(t_ast *root)
{
	return (((t_token *)root->item)->type);
}

int			all_token_are_var(t_command *root)
{
	size_t		i;

	i = 0;
	while (i < root->tok_size)
		if (root->tokens[i++].type != TOKEN_VAR)
			return (0);
	return (1);
}
