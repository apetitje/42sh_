/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_glob_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 13:03:36 by clabouri          #+#    #+#             */
/*   Updated: 2017/09/11 19:03:33 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

static char	*get_wordend(char *str, char *sep, char *jump)
{
	char *tmp;

	while (str && *str && !ft_strchr(sep, *str))
	{
		if (*str == '\\')
		{
			str += 1 + (*(str + 1) != 0);
			continue ;
		}
		if (!*str || ft_strchr(sep, *str))
			break ;
		if (*str != ']' && *str != '}' && (tmp = ft_strchr(jump, *str)))
			str = (ft_strchr(str + 1, *(tmp + 1))) ?
				ft_strchr(str + 1, *(tmp + 1)) : str;
		str++;
	}
	return (str - 1);
}

static int	count_word(char *str, char *sep, char *jump)
{
	int ret;

	ret = 0;
	while (str && *str)
	{
		while (*str && ft_strchr(sep, *str))
			if (*(str++) == '\\')
				break ;
		if (!*str)
			break ;
		str = get_wordend(str, sep, jump) + 1;
		ret++;
	}
	return (ret);
}

char		**sh_split(char *str, char *sep, char *jump)
{
	char	**ret;
	char	*tmp;
	int		i;

	if (!str || !sep || !(ret = ft_memalloc(sizeof(char*)
						* (count_word(str, sep, jump) + 1))))
		exit_prog(EXIT_FAILURE, "Malloc error (sh_split)\n");
	i = 0;
	while (*str)
	{
		while (*str && ft_strchr(sep, *str))
			if (*(str++) == '\\')
				break ;
		if (!*str)
			break ;
		tmp = get_wordend(str, sep, jump) + 1;
		if (!(ret[i++] = ft_strndup(str, tmp - str)))
			exit_prog(EXIT_FAILURE, "Malloc error (sh_split)\n");
		str = tmp;
	}
	ret[i] = NULL;
	return (ret);
}

char		*sh_chr(char *str, char c, char *jump)
{
	char *tmp;

	while (str && *str)
	{
		if (*str == '\\')
		{
			str += 1 + (*(str + 1) != 0);
			continue ;
		}
		if (!*str)
			return (NULL);
		if (*str == c)
			return (str);
		if ((tmp = ft_strchr(jump, *str)))
			str = (ft_strchr(str + 1, *(tmp + 1)))
				? ft_strchr(str + 1, *(tmp + 1)) : str;
		str++;
	}
	return (NULL);
}

char		*sh_rchr(char *str, char c, char *jump)
{
	char	*tmp;
	char	*ret;

	ret = str;
	tmp = str;
	while ((tmp = sh_chr(tmp, c, jump)))
		ret = tmp++;
	return ((ret == str && *str != c) ? NULL : ret);
}
