/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_read_set_read_opt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 12:13:20 by oyagci            #+#    #+#             */
/*   Updated: 2017/10/04 12:12:11 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		set_read_opt_type(char *opt_s, char *argv, t_read_opt *opt)
{
	if (is_opt_c(opt_s, 'd'))
		opt->delim = argv[0];
	else if (is_opt_c(opt_s, 'n'))
	{
		opt->nb_char_active = 1;
		if ((opt->nb_char = get_nb(argv)) < 0)
		{
			ft_printf("read: %s: invalid number\n", argv);
			return (-1);
		}
	}
	else if (is_opt_c(opt_s, 'p'))
		opt->prompt = argv;
	else if (is_opt_c(opt_s, 't'))
	{
		if (*argv == '-' || (opt->timeout = get_nb(argv)) < 0)
		{
			ft_dprintf(2, "history: %s: invalid timeout specification\n",
					argv);
			return (-1);
		}
	}
	else if (is_opt_c(opt_s, 'u'))
		opt->fd_in = ft_atoi(argv);
	return (0);
}

int		set_read_opt_arg(char *argv[], int *i, int *argc, t_read_opt *opt)
{
	char *const	options[] = { "-d", "-n", "-p", "-t", "-u", 0 };
	int			j;
	int			is;

	j = 0;
	is = 0;
	while (0 != options[j])
	{
		if (is_opt_c(argv[*i], options[j][1]))
		{
			is = 1;
			break ;
		}
		j += 1;
	}
	if (is)
	{
		if ((*i)++ + 1 < *argc)
			set_read_opt_type(options[j], argv[*i], opt) == -1 ? (is = -1) : 0;
		else
			return (-1);
		*i += 1;
	}
	return (is);
}

int		set_read_opt_simple(char *argv[], int *i, t_read_opt *opt)
{
	if (argv && argv[*i] && argv[*i][0] == '-')
	{
		if (is_opt_c(argv[*i], 'e'))
			opt->use_readline = 1;
		else if (is_opt_c(argv[*i], 'r'))
			opt->ign_bslash = 1;
		else if (is_opt_c(argv[*i], 's'))
			opt->silent = 1;
		else
			return (-1);
	}
	else
		return (0);
	*i += 1;
	return (1);
}

int		set_read_opt(char **argv[], int *argc, t_read_opt *opt)
{
	int		i;
	int		ret;

	i = 1;
	while (1)
	{
		if ((ret = set_read_opt_arg(*argv, &i, argc, opt)) > 0)
			;
		else if (ret == -1)
			break ;
		else if ((ret = set_read_opt_simple(*argv, &i, opt)) > 0)
			;
		else
			break ;
		if (i >= *argc)
			break ;
	}
	return (ret < 0 ? -1 : i);
}
