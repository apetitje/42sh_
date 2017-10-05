/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 17:16:40 by hanguelk          #+#    #+#             */
/*   Updated: 2017/10/01 19:54:15 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int				addelem_hashtable(char **elem)
{
	char	**bk;

	if (!(*elem))
	{
		ft_dprintf(2, "42sh: hash: -p: option requires an argument\n");
		display_hashusage(0);
		return (2);
	}
	if (*(elem + 1) == NULL)
		return (1);
	bk = &elem[1];
	while (*bk)
		hashtable_add(&g_hash, *bk++, elem[0], 0);
	return (0);
}

int				dispatch(int opt, char **ar)
{
	if (opt == 1)
		return (addelem_hashtable(ar));
	else if (opt == 2)
		return (hashtable_removecell(ar));
	else if (opt == 3)
		return (hashtable_free(&g_hash));
	else if (opt == 4)
		return (display_hashtable(1));
	else if (opt == 5)
		return (hashtable_print_data(ar));
	return (0);
}

static void		parse_opt_hash(t_command *args, int *i, int *res)
{
	int	opt;

	opt = 0;
	while (*(args->argv[1] + *i))
	{
		if (*(args->argv[1] + *i) == 'p')
			opt = 1;
		else if (*(args->argv[1] + *i) == 'd')
			opt = 2;
		else if (*(args->argv[1] + *i) == 'r')
			opt = 3;
		else if (*(args->argv[1] + *i) == 'l')
			opt = 4;
		else if (*(args->argv[1] + *i) == 't')
			opt = 5;
		else
		{
			display_hashusage(*(args->argv[1] + *i));
			*res = 2;
			return ;
		}
		(*i)++;
	}
	*res = dispatch(opt, &args->argv[2]);
}

int				ft_hash(t_bt_args ar)
{
	int			res;
	int			bk_fd[3];
	int			i;

	make_stdfd_bk((int*)bk_fd);
	if (do_redirect(ar.cmd))
	{
		restore_stdfd((int*)bk_fd);
		return (1);
	}
	res = 0;
	i = 1;
	if (ar.cmd->argc == 1)
		display_hashtable(0);
	else if (*(ar.cmd->argv[1]) == '-')
		parse_opt_hash(ar.cmd, &i, &res);
	else
		res = hash_search(&ar.cmd->argv[1], ar.env);
	restore_stdfd((int*)bk_fd);
	return (res);
}
