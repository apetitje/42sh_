/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 14:46:00 by hanguelk          #+#    #+#             */
/*   Updated: 2017/10/03 20:16:06 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static int	usage_and_error(char x)
{
	ft_dprintf(2, "42sh: unset: -%c: invalid option\n", x);
	ft_dprintf(2, "unset: usage: unset [-v][name ...]\n");
	return (2);
}

static int	parse_unset_opt(t_bt_args ar)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (ar.cmd->argv[i])
	{
		if (ar.cmd->argv[i][0] == '-')
		{
			while (++j && ar.cmd->argv[i][j])
				if (ar.cmd->argv[i][j] != 'v')
					return (usage_and_error(ar.cmd->argv[i][j]));
		}
		else
			break ;
		i++;
		j = 0;
	}
	if (!g_currjob->pipeline)
	{
		del_multi_var(&ar.cmd->argv[i], 0, 0);
		return (del_multi_var(&ar.cmd->argv[i], 1, 0));
	}
	else
		return (0);
}

int			unset_bt(t_bt_args ar)
{
	int	bk_fd[3];
	int	res;

	res = 0;
	make_stdfd_bk((int *)bk_fd);
	if (do_redirect(ar.cmd))
	{
		restore_stdfd((int*)bk_fd);
		return (1);
	}
	if (ar.cmd->argc != 1)
		res = parse_unset_opt(ar);
	restore_stdfd((int*)bk_fd);
	return (res);
}
