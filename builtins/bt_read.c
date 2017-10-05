/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 12:14:13 by oyagci            #+#    #+#             */
/*   Updated: 2017/10/03 14:54:28 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void	free_vars(char **vars, int nb)
{
	int	i;

	i = 0;
	while (i < nb && vars[i])
	{
		free(vars[i]);
		i += 1;
	}
	free(vars);
}

int		bt_read_then_next(int names_index, t_command *command, char **vars)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	j = 0;
	status = 0;
	while (names_index + i < command->argc || vars[j])
	{
		if (vars[j])
		{
			if (0 != set_variable(command->argv[names_index + i], vars[j]))
				status = 1;
			j += 1;
		}
		else if (0 != set_variable(command->argv[names_index + i], ""))
			status = 1;
		i += 1;
	}
	free_vars(vars, command->argc);
	return (status);
}

int		bt_read_then(t_read_opt *opt, t_command *command, int names_index)
{
	char	*str;
	char	**vars;
	int		i;
	int		status;

	status = 0;
	if (NULL != (str = get_input(opt)))
	{
		vars = parse_variables(str, command->argc - names_index);
		free(str);
		i = 0;
		if (names_index + i == command->argc)
		{
			set_variable("REPLY", vars[i]);
			free(vars[i]);
			free(vars);
			return (0);
		}
		status = bt_read_then_next(names_index, command, vars);
		return (status);
	}
	return (1);
}

int		fd_is_valid(int fd)
{
	int	flags;

	flags = fcntl(fd, F_GETFD);
	if (flags == -1)
	{
		ft_dprintf(2, "read: %d: Bad file descriptor\n", fd);
		return (0);
	}
	return (1);
}

int		bt_read(t_bt_args ar)
{
	int			bk_fd[3];
	int			names_index;
	t_read_opt	opt;
	int			ret;

	make_stdfd_bk(bk_fd);
	if (do_redirect(ar.cmd) > 0)
		return (1);
	ft_bzero(&opt, sizeof(opt));
	names_index = set_read_opt(&ar.cmd->argv, &ar.cmd->argc, &opt);
	if (!fd_is_valid(opt.fd_in))
	{
		restore_stdfd(bk_fd);
		return (1);
	}
	if (names_index < 0)
	{
		read_usage();
		restore_stdfd(bk_fd);
		return (1);
	}
	ret = bt_read_then(&opt, ar.cmd, names_index);
	restore_stdfd(bk_fd);
	return (ret);
}
