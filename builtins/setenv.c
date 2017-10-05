/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 12:12:24 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/01 21:12:29 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static	int		check_correct(t_bt_args ar)
{
	int r;
	int i;

	r = 0;
	i = -1;
	if (!ft_isalpha(ar.cmd->argv[1][0]))
		r = ft_dprintf(2, "setenv: Variable name must begin with a letter.\n");
	while (ar.cmd->argv[1][++i])
		if (!ft_isalpha(ar.cmd->argv[1][i]) && !ft_isdigit(ar.cmd->argv[1][i])
				&& ar.cmd->argv[1][i] != '_')
		{
			r = ft_dprintf(2, \
			"setenv: Variable name must contain alphanumeric characters.\n");
			break ;
		}
	return (r);
}

int				set_env(t_bt_args ar)
{
	int			i;
	int			r;
	int			bk_fd[3];

	make_stdfd_bk((int*)bk_fd);
	if (do_redirect(ar.cmd))
	{
		restore_stdfd((int*)bk_fd);
		return (1);
	}
	i = -1;
	if (!ar.cmd->argv[1])
	{
		print_env(ar.env);
		restore_stdfd((int*)bk_fd);
		return (0);
	}
	r = (ar.cmd->argc > 3) ? ft_dprintf(2, "setenv: Too many arguments.\n") : 0;
	r = check_correct(ar);
	if (!r && !g_currjob->pipeline)
		add_to_env(ar.cmd->argv[1],
				(ar.cmd->argv[2]) ? ar.cmd->argv[2] : "", &g_env);
	restore_stdfd((int*)bk_fd);
	return ((r) ? 1 : 0);
}
