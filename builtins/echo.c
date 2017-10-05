/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:54:09 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/03 19:54:33 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static int	find_echap(char **line, char flags[100], char *echap)
{
	if (**line == 't')
		*echap = '\t';
	else if (**line == 'v')
		*echap = '\v';
	else if (**line == 'n')
		*echap = '\n';
	else if (**line == 'r')
		*echap = '\r';
	else if (**line == 'f')
		*echap = '\f';
	else if (**line == 'a')
		*echap = '\a';
	else if (**line == 'b')
		*echap = '\b';
	else if (**line == 'c')
	{
		ft_strcat(flags, "n");
		return (2);
	}
	if (*echap)
		write(1, echap, 1);
	return (0);
}

static int	ft_echap(char *s, int flag, char flags[100])
{
	char	*line;
	char	echap;

	line = s;
	while (*line)
	{
		echap = 0;
		if (flag && *line == '\\')
		{
			++line;
			if (find_echap(&line, flags, &echap))
				return (2);
		}
		if (!echap)
			write(1, line, 1);
		++line;
	}
	return (0);
}

static int	find_flags(t_command *command, int *j, char flags[])
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	ft_bzero(flags, 100);
	while (command->argv[1][i] && (command->argv[1][i] == 'n'
				|| command->argv[1][i] == 'e'))
	{
		(i <= 100) ? flags[i - 1] = command->argv[1][i] : 0;
		if (command->argv[1][i] == 'e')
			flag = 1;
		++i;
	}
	(!command->argv[1][i] && flags[0]) ? ++(*j) : ft_bzero(flags, 100);
	return (flag);
}

static void	echo_main(t_bt_args ar, char flags[100], int flag)
{
	int	i;
	int	j;

	if (ar.cmd->argc >= 2 && !(j = 0))
	{
		flag = (ar.cmd->argv[1][0] == '-') ? find_flags(ar.cmd, &j, flags) : 0;
		i = -1;
		while (ar.cmd->argv[++j])
		{
			(++i) ? write(1, " ", 1) : 0;
			if (flag && ft_echap(ar.cmd->argv[j], flag, flags) == 2)
				break ;
			else if (!flag)
				ft_putstr(ar.cmd->argv[j]);
		}
	}
	if (!ft_strchr(flags, 'n'))
		ft_putendl("");
}

int			ft_echo(t_bt_args ar)
{
	char	flags[100];
	int		flag;
	int		bk_fd[3];

	flags[0] = 0;
	flag = 0;
	make_stdfd_bk((int*)bk_fd);
	if (do_redirect(ar.cmd))
	{
		restore_stdfd((int*)bk_fd);
		return (1);
	}
	echo_main(ar, flags, flag);
	restore_stdfd((int*)bk_fd);
	return (0);
}
