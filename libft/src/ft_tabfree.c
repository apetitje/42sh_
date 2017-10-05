/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:37:48 by clabouri          #+#    #+#             */
/*   Updated: 2017/06/16 08:36:19 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_tabfree(char **tab)
{
	int i;

	if (!tab)
		return ;
	i = ft_tablen(tab);
	while (i--)
		free(tab[i]);
	free(tab);
	tab = NULL;
}
