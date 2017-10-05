/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_brace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 20:05:39 by clabouri          #+#    #+#             */
/*   Updated: 2017/09/24 17:58:57 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

static char		*join_expr(char *ltab, char *word, char *end)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	tmp = sh_chr(word, '{', "\"\"[]''``");
	ret = malloc(tmp - word
			+ ft_strlen(ltab) + ft_strlen(end) + (*ltab == '`') + 1);
	if (!ret)
		exit_prog(EXIT_FAILURE, "Malloc error (apply_brck)\n");
	ft_strncpy(ret, word, tmp - word);
	if (*ltab == '`')
		ft_strcat(ret, "\\");
	ft_strcat(ret, ltab);
	ft_strcat(ret, end);
	return (ret);
}

static t_list	*apply_brck(char **ltab, char *word, char *end)
{
	char	**tmp;
	char	*stmp;
	t_list	*new;
	t_list	*ret;

	tmp = ltab;
	ret = NULL;
	while (*tmp)
	{
		stmp = *tmp;
		*tmp = join_expr(stmp, word, end);
		free(stmp);
		new = sh_glob(ft_strdup(*tmp));
		if (!new)
		{
			if (!(new = ft_lstnew(*tmp, ft_strlen(*tmp))))
				exit_prog(EXIT_FAILURE, "Malloc error (multi_glob)");
		}
		else
			free(*tmp);
		ft_lstappend(&ret, new);
		tmp++;
	}
	free(ltab);
	return (ret);
}

static char		*last_brack(char *word)
{
	static char	array[] = "{}[]\"\"''``";
	char		*tmp;
	char		*ret;

	ret = sh_chr(word, '{', "\"\"[]''``");
	if (!(ret++))
		return (NULL);
	while (ret && *ret != '}')
	{
		if (!*ret)
			return (NULL);
		if (*ret == '\\')
		{
			ret += 1 + (*(ret + 1) != 0);
			continue ;
		}
		if (*ret == '}')
			break ;
		if (*ret != ']' && (tmp = ft_strchr(array, *ret)))
			if (!(ret = ft_strchr(ret + 1, *(tmp + 1))))
				return (NULL);
		ret++;
	}
	return (ret);
}

t_list			*sh_brace(char *word)
{
	t_list	*ret;
	char	**ltab;
	char	*tmp2;
	char	*tmp;

	if (!(tmp = last_brack(word)))
		return (NULL);
	*tmp = 0;
	if (!(tmp2 = sh_chr(word, '{', "[]\"\"''")))
		return (NULL);
	ltab = sh_build_exprs(tmp2 + 1);
	ret = apply_brck(ltab, word, tmp + 1);
	if (ret)
		ft_strdel(&word);
	return (ret);
}
