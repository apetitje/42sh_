/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 14:28:59 by oyagci            #+#    #+#             */
/*   Updated: 2017/10/02 17:37:33 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int			print_history_nb(t_hist_opt *opt)
{
	t_list	*head;
	int		nb;
	int		i;
	int		count;

	count = get_hist_count(g_hist);
	head = g_hist;
	nb = ft_atoi(opt->value);
	i = nb;
	while (i > 1 && head->next)
	{
		head = head->next;
		i -= 1;
	}
	i = 1;
	nb > count ? (nb = count) : 0;
	while (head)
	{
		ft_printf("%6d  %s\n", (count - nb) + i, get_hist(head));
		head = head->prev;
		i += 1;
	}
	return (0);
}

static int	get_opt_type(char *c)
{
	if (is_opt_c(c, 'c'))
		return (HIST_CLEAR);
	else if (is_opt_c(c, 'd'))
		return (HIST_DELETE);
	else if (is_opt_c(c, 'a'))
		return (HIST_APPEND);
	else if (is_opt_c(c, 'n'))
		return (HIST_NEWLINES);
	else if (is_opt_c(c, 'r'))
		return (HIST_READHIST);
	else if (is_opt_c(c, 'w'))
		return (HIST_WRITEHIST);
	else if (is_opt_c(c, 'p'))
		return (HIST_PRINTHIST);
	else if (is_opt_c(c, 's'))
		return (HIST_ADDARGS);
	else if (c != 0)
		return (HIST_ERRTYPE);
	return (0);
}

t_hist_opt	*history_get_opt(int ac, char *av[])
{
	t_hist_opt	*opt;

	if (NULL == (opt = ft_memalloc(sizeof(t_hist_opt))))
		exit_prog(EXIT_FAILURE, "Malloc error (history_get_opt)");
	opt->type = HIST_PRINTHIST;
	opt->value = 0;
	if (ac <= 1)
		return (opt);
	else if (av[1][0] == '-')
	{
		opt->type = get_opt_type(av[1]);
		opt->value = av[2];
		opt->av = av + 2;
	}
	else if (av[1][0] >= '0' && av[1][0] <= '9')
	{
		opt->type = HIST_HISTNB;
		opt->value = av[1];
	}
	else
		opt->type = HIST_HISTERR;
	return (opt);
}

int			apply_history(t_hist_opt *opt)
{
	if (opt->type == HIST_PRINTHIST)
		return (print_history());
	else if (opt->type == HIST_CLEAR)
		return (clear_history());
	else if (opt->type == HIST_DELETE)
		return (history_delete(opt));
	else if (opt->type == HIST_READHIST)
		return (history_read(opt));
	else if (opt->type == HIST_WRITEHIST)
		return (write_history(opt));
	else if (opt->type == HIST_ADDARGS)
		return (history_add_args(opt));
	else if (opt->type == HIST_ERRTYPE)
		return (history_usage());
	else if (opt->type == HIST_HISTNB)
		return (print_history_nb(opt));
	else if (opt->type == HIST_HISTERR)
		return (print_expected());
	else if (opt->type == HIST_APPEND)
		return (0);
	return (1);
}

int			builtin_history(t_bt_args ar)
{
	int			bk_fd[3];
	int			ret;
	t_hist_opt	*opt;

	make_stdfd_bk(bk_fd);
	if (do_redirect(ar.cmd))
		return (1);
	opt = history_get_opt(ar.cmd->argc, ar.cmd->argv);
	ret = apply_history(opt);
	free(opt);
	restore_stdfd(bk_fd);
	return (ret);
}
