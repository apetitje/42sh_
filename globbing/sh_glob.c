/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 19:03:43 by clabouri          #+#    #+#             */
/*   Updated: 2017/09/24 17:59:34 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

static void		escape_move(char *tmp)
{
	ft_memmove(tmp + 1, tmp, ft_strlen(tmp) + 1);
	*tmp = '\\';
}

static char		*epure(char *word, char *del, char *escape)
{
	char	*tmp;
	char	*ret;

	if (!(ret = malloc(sh_count_ep(word, del, escape) + 1)))
		exit_prog(EXIT_FAILURE, "Malloc error (epure)\n");
	ft_strcpy(ret, word);
	while (*del)
	{
		tmp = ret;
		while ((tmp = sh_chr(tmp, *del, "\"\"''")))
		{
			if (!sh_chr(tmp + 1, *del, "\"\"''") || !ft_strcpy(tmp, tmp + 1))
				break ;
			while (*tmp && (*tmp != *del))
			{
				if (ft_strchr(escape, *tmp))
					escape_move(tmp++);
				tmp++;
			}
			(*tmp) ? ft_strcpy(tmp, tmp + 1) : tmp;
		}
		del++;
	}
	ft_strdel(&word);
	return (ret);
}

t_list			*sh_wc_and_dot(char *wd, char *path)
{
	char			*tmp;
	t_list			*matches;
	DIR				*o_dir;
	struct dirent	*r_dir;

	matches = NULL;
	if (path && (sh_chr(path, '*', "\"\"''") || sh_chr(path, '?', "\"\"''")))
		return (sh_oc_in_path(wd, path));
	sh_rmbs(tmp = (path) ? ft_strdup(path) : NULL);
	if (path && !tmp)
		exit_prog(EXIT_FAILURE, "Malloc error (sh_wc_and_dot)\n");
	if (!(o_dir = opendir((path) ? tmp : "./")))
		return (free_ret_null((void**)&tmp, NULL, NULL, NULL));
	(path) ? ft_strdel(&tmp) : path;
	wd = (sh_chr(wd, '/', "\"\"''")) ? sh_rchr(wd, '/', "\"\"''") + 1 : wd;
	while ((r_dir = readdir(o_dir)))
		if (*r_dir->d_name != '.' && sh_match(wd, r_dir->d_name))
		{
			if (!(tmp = ft_strjoin(path, r_dir->d_name)))
				exit_prog(EXIT_FAILURE, "Malloc error (sh_wc_and_dot)");
			ft_lstappend(&matches, ft_lstnew(tmp, ft_strlen(tmp)));
		}
	closedir(o_dir);
	return (matches);
}

t_list			*sh_glob(char *word)
{
	t_list	*ret;
	char	*path;
	char	*tmp;

	if (!word)
		exit_prog(EXIT_FAILURE, "Malloc error (multi_glob)");
	if (sh_chr(word, '"', "\"\"''") || sh_chr(word, '\'', "\"\"''"))
		word = epure(word, "\"'", "\\{}[]*?\"'-!");
	ret = NULL;
	if ((tmp = sh_chr(word, '{', "[]\"\"''``"))
			&& sh_chr(tmp + 1, '}', "[]\"\"''``"))
		if ((ret = sh_brace(word)))
			return (ret);
	if ((tmp = sh_chr(word, '[', "\"\"''``"))
			&& sh_chr(tmp + 1, ']', "\"\"''``"))
		if ((ret = sh_range(word)))
			return (ret);
	path = sh_search_path(word, 0);
	ret = sh_wc_and_dot(word, path);
	free(word);
	free(path);
	return (ret);
}
