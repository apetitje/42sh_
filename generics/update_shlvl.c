/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 18:24:35 by apetitje          #+#    #+#             */
/*   Updated: 2017/09/28 18:24:55 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		update_shlvl(t_list **env)
{
	int		lvl;
	char	*lvl_str;

	lvl = 0;
	if ((lvl_str = search_var_in_env(*env, "SHLVL")))
		lvl = ft_atoi(lvl_str);
	lvl_str = NULL;
	ft_asprintf(&lvl_str, "%d", lvl + 1);
	add_to_env("SHLVL", lvl_str, env);
	ft_memdel((void **)&lvl_str);
}
