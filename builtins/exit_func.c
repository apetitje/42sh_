/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 10:00:10 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/04 11:19:56 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void		exit_prog(int code, char *err)
{
	if (err)
		ft_dprintf(2, "%s", err);
	exit(code);
}

void		free_all(void)
{
	free_env(&g_env);
	free_env(&g_locales);
	free_env(&g_exported);
	free_tok_tab(&g_tok_tab);
	free_ast(g_root);
	free_hist(&g_hist);
	ft_memdel((void **)&g_clipboard);
}

static void	check_correct(t_bt_args ar, int *bkfd, int i)
{
	while (ar.cmd->argv[1][++i])
		if (!ft_isdigit(ar.cmd->argv[1][i]))
		{
			ft_dprintf(2, \
					"42sh: exit: %s: numeric argument required\n",\
					ar.cmd->argv[1]);
			restore_stdfd((int*)bkfd);
			if (g_currjob->pipeline)
				break ;
			else
				exit(1);
		}
}

static	int	exit_or_not(int i)
{
	if (!g_currjob->pipeline && !display_exit_jobs())
	{
		free_all();
		exit(i);
	}
	else
		return (0);
}

int			exit_func(t_bt_args ar)
{
	int		i;
	int		bk_fd[3];

	i = -1;
	make_stdfd_bk((int*)bk_fd);
	if (do_redirect(ar.cmd))
	{
		restore_stdfd((int*)bk_fd);
		return (1);
	}
	if (ar.cmd->argc > 2)
	{
		ft_dprintf(2, "42sh: exit: too many arguments\n");
		restore_stdfd((int*)bk_fd);
		return (1);
	}
	else if (ar.cmd->argv[1])
		check_correct(ar, (int*)bk_fd, i);
	restore_stdfd((int*)bk_fd);
	i = (ar.cmd->argv[1]) ? ft_atoi(ar.cmd->argv[1]) : g_exit_status;
	return (exit_or_not(i));
}
