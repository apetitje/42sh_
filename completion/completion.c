/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 20:29:03 by apetitje          #+#    #+#             */
/*   Updated: 2017/08/09 19:06:58 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static void	end_completion(t_list *matches, t_i_line *i_line, char *before)
{
	int		i;

	if ((i = count_list_ele(matches)) == 1)
	{
		curs_erase_command(i_line);
		ft_free_buff(&i_line->input);
		i_line->cursor.x = 0;
		i_line->cursor.y = 0;
		if (before)
		{
			print_and_progress_curs(before, i_line);
			ft_fill_buff(&i_line->input, before,
					ft_strlen(before));
		}
		print_and_progress_curs(matches->data, i_line);
		ft_fill_buff(&i_line->input, matches->data,
				ft_strlen(matches->data));
		print_and_restore_curs(i_line->tmp, i_line);
	}
	else if (i)
	{
		tputs(tgetstr("cd", NULL), 0, ft_putchar);
		g_last_cmpl = 0;
		cmpl_cols(i_line, matches);
	}
}

static int	init_to_find(t_i_line *i_line, char **to_find, char **before)
{
	size_t		i;

	*to_find = NULL;
	i = 0;
	while (i_line->input.data[i] == ' ' || i_line->input.data[i] == '\t'
			|| i_line->input.data[i] == '\n')
		++i;
	if (!(i_line->input.data[i]))
		return (0);
	ft_asprintf(before, "%.*s", i, i_line->input.data);
	if (!(*to_find = ft_strdup(i_line->input.data + i)))
		exit_prog(EXIT_FAILURE, "Malloc error\n");
	return (ft_strlen(*to_find));
}

void		completion(t_i_line *i_line)
{
	t_list		*mtch;
	int			i;
	char		*before;
	char		*to_find;
	size_t		find_len;

	before = NULL;
	mtch = NULL;
	i = -1;
	if (!(find_len = init_to_find(i_line, &to_find, &before)))
		if (!(to_find = ft_strdup("")))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
	if (!ft_strchr(to_find, ' '))
	{
		if (*to_find == '$')
			comp_var(&mtch, to_find, find_len, 0);
		else
			complete_first(&mtch, to_find, find_len, &before);
	}
	else
		complete_second(i_line->input.data, &before, &mtch);
	end_completion(mtch, i_line, before);
	free_list(&mtch);
	ft_memdel((void **)&before);
	ft_memdel((void **)&to_find);
}
