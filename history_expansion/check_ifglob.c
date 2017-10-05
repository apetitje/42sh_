/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ifglob.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:33:12 by clabouri          #+#    #+#             */
/*   Updated: 2017/09/24 21:49:48 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int	check_ifglob(char *line, char *op_ptr)
{
	char	*tmp;
	char	*tmp2;

	if (line == op_ptr || *(op_ptr - 1) != '[')
		return (0);
	if (!(tmp = sh_chr(op_ptr, ']', "\"\"''")))
		return (0);
	if ((tmp2 = sh_chr(op_ptr, ' ', "\"\"''")) && tmp2 < tmp)
		return (0);
	return (1);
}
