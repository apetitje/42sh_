/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 12:28:01 by apetitje          #+#    #+#             */
/*   Updated: 2017/06/05 22:23:31 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*get_hist(t_list *ele)
{
	return (((t_hist *)ele->data)->content);
}

int		get_select(t_list *ele)
{
	return (((t_hist *)ele->data)->select);
}

char	*get_var(t_list *ele)
{
	return (((t_var *)ele->data)->var);
}

char	*get_content(t_list *ele)
{
	return (((t_var *)ele->data)->content);
}
