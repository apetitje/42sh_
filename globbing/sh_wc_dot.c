/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_wc_dot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 17:16:16 by clabouri          #+#    #+#             */
/*   Updated: 2017/08/12 21:40:32 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

static char		*next_oc(char *path)
{
	char	*wc;
	char	*dot;

	dot = sh_chr(path, '?', "\"\"''");
	wc = sh_chr(path, '*', "\"\"''");
	if (!dot && !wc)
		return (path);
	if (!dot && wc)
		return (wc);
	if (dot && !wc)
		return (dot);
	return ((dot > wc) ? wc : dot);
}

static t_list	*call_wd(char *word, char *path, char *nwd)
{
	char	*tmp;
	t_list	*matches;

	nwd = sh_escape(nwd, "\"'`*?[]{}\\");
	tmp = sh_chr(next_oc(word), '/', "\"\"''");
	if (!(nwd = ft_strjoinfree(ft_strjoinfree(path, nwd, 2), tmp, 1)))
		exit_prog(EXIT_FAILURE, "Malloc error (call_wd)\n");
	path = sh_search_path(nwd, 0);
	matches = sh_wc_and_dot(nwd, path);
	ft_strdel(&nwd);
	ft_strdel(&path);
	return (matches);
}

int				sh_match(char *s1, char *s2)
{
	if (!*s1 && !*s2)
		return (1);
	if (!*s2 && *s1 == '*')
		return (sh_match(s1 + 1, s2));
	if (*s1 == '\\' && *(s1 + 1) == *s2)
		return (sh_match(s1 + 2, s2 + 1));
	if (*s1 == '*')
		return (sh_match(s1 + 1, s2) || sh_match(s1, s2 + 1));
	if (*s1 == *s2 || (*s1 == '?' && *s2))
		return (sh_match(s1 + 1, s2 + 1));
	return (0);
}

char			*sh_search_path(char *word, int kslash)
{
	char	*slash;
	char	*ret;

	if (!(slash = sh_rchr(word, '/', "\"\"''")))
		return (NULL);
	if (*(slash + 1) == 0 && !kslash)
	{
		*slash = 0;
		return (sh_search_path(word, 0));
	}
	if (!(ret = ft_strndup(word, slash - word + 1)))
		exit_prog(EXIT_FAILURE, "Malloc error (sh_search_path)\n");
	return (ret);
}

t_list			*sh_oc_in_path(char *word, char *path)
{
	t_list			*matches;
	DIR				*o_dir;
	struct dirent	*r_dir;
	char			*nwd;
	char			*tmp;

	matches = NULL;
	if (!(nwd = ft_strndup(path,
			sh_chr(next_oc(path), '/', "\"\"''") - path)))
		exit_prog(EXIT_FAILURE, "Malloc error (sh_oc_in_path)\n");
	path = sh_search_path(nwd, 0);
	sh_rmbs(tmp = (path) ? ft_strdup(path) : NULL);
	if (!(o_dir = opendir((tmp) ? tmp : "./")))
		return (free_ret_null((void**)&tmp, (void**)&nwd, (void**)&path, NULL));
	(path) ? ft_strdel(&tmp) : path;
	tmp = (sh_chr(nwd, '/', "\"\"''")) ?
			sh_rchr(nwd, '/', "\"\"''") + 1 : nwd;
	while ((r_dir = readdir(o_dir)))
		if (*r_dir->d_name != '.' && sh_match(tmp, r_dir->d_name))
			ft_lstappend(&matches, call_wd(word, path, r_dir->d_name));
	ft_strdel(&nwd);
	ft_strdel(&path);
	closedir(o_dir);
	return (matches);
}
