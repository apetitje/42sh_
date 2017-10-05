/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:06:10 by clabouri          #+#    #+#             */
/*   Updated: 2017/10/03 11:54:17 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

static void		add_range(char **range, char c1, char c2)
{
	char	*tmp;

	if (c2 < c1)
		return ;
	if (!(tmp = malloc(c2 - c1 + 2)))
		exit_prog(EXIT_FAILURE, "Malloc error (add_range)");
	*tmp = 0;
	if (!ft_isprint(c1))
	{
		free(tmp);
		return ;
	}
	while (c1 <= c2)
	{
		if (c1 != '/' && !(*range && ft_strchr(*range, c1))
						&& !ft_strchr(tmp, c1))
			ft_strncat(tmp, &c1, 1);
		c1++;
	}
	if (*tmp && !(*range = ft_strjoinfree(*range, tmp, 1)))
		exit_prog(EXIT_FAILURE, "Malloc error (add_range)\n");
	free(tmp);
}

static char		*get_last(char *word)
{
	char	*ret;
	char	*beg;

	word += (*word == '!' || *word == '^');
	beg = word;
	while (*word)
	{
		if (!(ret = sh_chr(word, ']', "\"\"''")))
			return (NULL);
		if (ret != beg)
			break ;
		word++;
	}
	return (ret);
}

t_list			*sh_range(char *word)
{
	char	*range;
	char	*last;
	char	*tmp;
	int		rev;

	range = NULL;
	tmp = sh_chr(word, '[', "\"\"''") + 1;
	if (!(last = get_last(tmp)))
		return (NULL);
	rev = (*tmp == '!' || *tmp == '^') ? (tmp++ != 0) : 0;
	while (tmp != last && *tmp)
	{
		tmp = (*tmp == '\\') ? tmp + 1 : tmp;
		if (*(tmp + 1) == '-' && tmp + 2 != last && tmp++)
		{
			add_range(&range, *(tmp - 1), *(tmp + 1 + (*(tmp + 1) == '\\')));
			tmp = tmp + 2 + (*(tmp + 1) == '\\');
			continue ;
		}
		add_range(&range, *tmp, *tmp);
		tmp++;
	}
	return (sh_handle_range(word, range, rev));
}
