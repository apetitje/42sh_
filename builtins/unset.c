/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 17:00:09 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/01 21:14:45 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int					unset_var(t_list **tmp)
{
	set_var(*tmp, NULL);
	set_content(*tmp, NULL);
	free((*tmp)->data);
	ft_memdel((void **)tmp);
	return (0);
}

static void			unset_loop(t_command *command, t_list *p)
{
	t_list	*tmp;
	int		i;

	i = 1;
	while (command->argv[i])
	{
		while (p)
		{
			if (!ft_strcmp(get_var(p), command->argv[i]))
			{
				tmp = p;
				if (p->prev)
					p->prev->next = p->next;
				else
					g_env = p->next;
				if (p->next)
					p->next->prev = p->prev;
				unset_var(&tmp);
				break ;
			}
			p = p->next;
		}
		p = g_env;
		i++;
	}
}

int					unset_env(t_bt_args ar)
{
	t_list		*p;
	int			bk_fd[3];

	make_stdfd_bk((int*)bk_fd);
	p = g_env;
	if (do_redirect(ar.cmd))
	{
		restore_stdfd((int*)bk_fd);
		return (1);
	}
	if (!ar.cmd->argv[1])
	{
		ft_dprintf(2, "unsetenv: Too few arguments.\n");
		restore_stdfd((int*)bk_fd);
		return (1);
	}
	if (!g_currjob->pipeline)
	{
		if (!ft_strcmp(ar.cmd->argv[1], "PATH") && p == g_env)
			hashtable_free(&g_hash);
		unset_loop(ar.cmd, p);
	}
	restore_stdfd((int*)bk_fd);
	return (0);
}
