/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_brace2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 20:51:38 by clabouri          #+#    #+#             */
/*   Updated: 2017/09/24 14:28:04 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

static char	**build_nums(int range[])
{
	char	**ret;
	char	**tmp;
	int		len;

	len = range[0] - range[1];
	len = ((len < 0) ? -len : len) + 1;
	if (!(ret = malloc(sizeof(char*) * (len + 1))))
		exit_prog(EXIT_FAILURE, "Malloc error (build_nums)");
	tmp = ret;
	while (len--)
	{
		if (range[0] <= range[1])
		{
			if (!(*(tmp++) = ft_itoac(range[0]++)))
				exit_prog(EXIT_FAILURE, "Malloc error (build_nums)");
		}
		else if (!(*(tmp++) = ft_itoac(range[0]--)))
			exit_prog(EXIT_FAILURE, "Malloc error (build_nums)");
	}
	*tmp = NULL;
	return (ret);
}

static char	**brace_num(char *word)
{
	char	*last;
	int		range[2];

	last = ft_strrchr(word, '.') + 1;
	if ((!ft_isdigit(*word) && *word != '-' && *word != '+')
			|| (!ft_isdigit(*last) && *last != '-' && *last != '+'))
		return (NULL);
	if (!(word = ft_strndup(word, ft_strchr(word, '.') - word)))
		exit_prog(EXIT_FAILURE, "Malloc error (brace_num)");
	if (!ft_strnum(word + (*word == '-' || *last == '+'))
		|| !ft_strnum(last + (*last == '-' || *last == '+')))
	{
		free(word);
		return (NULL);
	}
	range[0] = ft_atoi(word);
	range[1] = ft_atoi(last);
	free(word);
	return (build_nums(range));
}

static char	**brace_range(char *word)
{
	char	**ret;
	char	**tmp;
	char	*last;
	int		len;

	if ((ret = brace_num(word)))
		return (ret);
	last = (word + ft_strlen(word) - 1);
	if (ft_isalpha(*word) && ft_isalpha(*last) && ft_strlen(word) == 4)
	{
		len = *last - *word;
		len = ((len < 0) ? -len : len) + 2;
		if (!(ret = malloc(sizeof(char*) * len)))
			exit_prog(EXIT_FAILURE, "Malloc error (brace_range)");
		tmp = ret;
		while (--len)
		{
			if (!(*(tmp++) = ft_strndup(word, 1)))
				exit_prog(EXIT_FAILURE, "Malloc error (brace_range)");
			*word += (*word > *last) ? -1 : 1;
		}
		*tmp = NULL;
		return (ret);
	}
	return (NULL);
}

char		**sh_build_exprs(char *word)
{
	char **ret;

	if (sh_chr(word, ',', "[]\"\"''"))
	{
		if (!(ret = sh_brcsplt(word)))
			exit_prog(EXIT_FAILURE, "Malloc error (build_exprs)");
		return (ret);
	}
	if (sh_match("*..*", word))
		if ((ret = brace_range(word)))
			return (ret);
	if (!(ret = malloc(sizeof(char*) * 2)))
		exit_prog(EXIT_FAILURE, "Malloc error (build_exprs)");
	if (!(*ret = malloc(ft_strlen(word) + 5)))
		exit_prog(EXIT_FAILURE, "Malloc error (build_exprs)");
	ft_strcpy(*ret, "\\{");
	ft_strcat(*ret, word);
	ft_strcat(*ret, "\\}");
	*(ret + 1) = NULL;
	return (ret);
}
