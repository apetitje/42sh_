/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_range2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 18:00:27 by clabouri          #+#    #+#             */
/*   Updated: 2017/10/01 18:46:52 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

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

static void		escape(char *pat, char c)
{
	if (ft_strchr("\\\"'`[]{}?*()!^", c))
		ft_strcat(pat, "\\");
	ft_strncat(pat, &c, 1);
}

static t_list	*test_char(char *word, char c)
{
	char	*tmp;
	char	*tmp2;
	char	*pat;
	t_list	*ret;

	tmp = sh_chr(word, '[', "\"\"''");
	tmp2 = get_last(tmp + 1) + 1;
	pat = ft_strnew(tmp - word + ft_strlen(tmp2)
				+ 2 + (ft_strchr("\"'*?", c) != 0));
	if (!pat)
		exit_prog(EXIT_FAILURE, "Malloc error (test_char)\n");
	ft_strncpy(pat, word, tmp - word);
	escape(pat, c);
	ft_strcat(pat, tmp2);
	ret = sh_glob(pat);
	return (ret);
}

t_list			*sh_handle_range(char *word, char *range, int rev)
{
	t_list	*ret;
	char	*tmp;
	char	c;

	ret = NULL;
	if (!(tmp = range) || !*range)
		return (NULL);
	if (!rev)
		while (*tmp)
			ft_lstappend(&ret, test_char(word, *(tmp++)));
	else
	{
		c = 31;
		while (++c < 127)
			if (c != '/' && !ft_strchr(range, c))
				ft_lstappend(&ret, test_char(word, c));
	}
	ft_strdel(&range);
	if (ret)
		ft_strdel(&word);
	return (ret);
}
