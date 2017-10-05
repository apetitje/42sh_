/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 02:32:09 by hanguelk          #+#    #+#             */
/*   Updated: 2017/10/05 02:45:52 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int		subshell_arithmetic(t_ast *root, char drct, char *line)
{
	char	*word;

	if (drct)
		word = ((t_token *)root->right->item)->word;
	else
		word = ((t_token *)root->left->item)->word;
	create_inline_job(NULL);
	if (!(line = ft_strdup(word)))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	return (open_subshell(&line, 0));
}
