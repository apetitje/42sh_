/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 12:41:24 by apetitje          #+#    #+#             */
/*   Updated: 2017/06/05 22:23:38 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	set_select(t_list *ele, int val)
{
	if (!ele || !ele->data)
		return ;
	((t_hist *)ele->data)->select = val;
}

void	set_hist(t_list *ele, char *content)
{
	if (!ele || !ele->data)
		return ;
	if (!content)
		ft_memdel((void **)&((t_hist *)ele->data)->content);
	else
		((t_hist *)ele->data)->content = content;
}

void	set_var(t_list *ele, char *content)
{
	if (!ele || !ele->data)
		return ;
	if (!content)
		ft_memdel((void **)&((t_var *)ele->data)->var);
	else
		((t_var *)ele->data)->var = content;
}

void	set_content(t_list *ele, char *content)
{
	if (!ele || !ele->data)
		return ;
	if (!content)
		ft_memdel((void **)&((t_var *)ele->data)->content);
	else
		((t_var *)ele->data)->content = content;
}
