/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 20:26:58 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 18:08:40 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void		comp_var(t_list **mtch, char *to_find, size_t find_len, int code)
{
	t_list	*env;
	char	*name;
	char	*var;
	char	flag;

	env = g_env;
	var = NULL;
	flag = 0;
	name = to_find + ((code) ? 0 : 1);
	if (!code)
		--find_len;
	while (env)
	{
		if (!ft_strncmp(get_var(env), name, find_len))
		{
			if (!code)
				ft_asprintf(&var, "$%s", get_var(env));
			else if (!(var = ft_strdup(get_var(env))))
				exit_prog(EXIT_FAILURE, "Malloc error (comp_var)\n");
			ft_lstaddback(mtch, ft_lstnew(var, sizeof(var)));
		}
		env = env->next;
		if (!env && !flag && (flag = 1))
			env = g_locales;
	}
}
