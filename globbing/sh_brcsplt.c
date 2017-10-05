/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_brcsplt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 15:09:19 by clabouri          #+#    #+#             */
/*   Updated: 2017/09/24 17:08:36 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

size_t	get_len(char *str)
{
	static char	array[] = "{}[]\"\"''";
	char		*tmp;
	size_t		ret;

	ret = 2;
	while (*str)
	{
		if (*str == '\\')
		{
			str += 1 + (*(str + 1) != 0);
			continue ;
		}
		if (*str != ']' && *str != '}' && (tmp = ft_strchr(array, *str)))
			if ((tmp = ft_strchr(str + 1, *(tmp + 1))))
				str = tmp;
		ret += (*(str++) == ',');
	}
	return (ret);
}

char	**sh_brcsplt(char *str)
{
	char	**ret;
	char	**tmp;
	char	*stmp;
	int		len;

	if (!str)
		return (NULL);
	len = get_len(str);
	if (!(ret = malloc(sizeof(char*) * len)))
		exit_prog(EXIT_FAILURE, "Malloc error (sh_brcsplt)");
	tmp = ret;
	while (--len)
	{
		stmp = sh_chr(str, ',', "{}[]\"\"''");
		stmp = (!stmp) ? str + ft_strlen(str) : stmp;
		if (!(*(tmp++) = ft_strndup(str, stmp - str)))
			exit_prog(EXIT_FAILURE, "Malloc error (sh_brcsplt)");
		str = stmp + (*stmp != 0);
	}
	*tmp = NULL;
	return (ret);
}
