/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_nanoset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 17:13:23 by hanguelk          #+#    #+#             */
/*   Updated: 2017/09/30 20:03:29 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void	display_all_vars(void)
{
	t_list	*current;
	char	flag;

	flag = 0;
	current = g_env;
	while (current)
	{
		ft_printf("%s=%s\n", get_var(current), get_content(current));
		current = current->next;
		if (!current && !flag && (++flag))
			current = g_locales;
		else if (!current && (flag == 1) && (++flag))
			current = g_exported;
	}
}

int		bt_nanoset(t_bt_args ar)
{
	int bkfd[3];

	make_stdfd_bk((int*)bkfd);
	do_redirect(ar.cmd);
	display_all_vars();
	restore_stdfd((int*)bkfd);
	return (0);
}
