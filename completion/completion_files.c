/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 19:00:15 by apetitje          #+#    #+#             */
/*   Updated: 2017/08/10 15:08:37 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static void	find_file_in_directory(char *dir_path, t_list **matches,
		char *name, size_t len)
{
	DIR			*dir;
	t_dirent	*f;
	char		*file_name;
	char		*path;

	path = NULL;
	file_name = NULL;
	if ((dir = opendir(dir_path)))
	{
		while ((f = readdir(dir)))
			if (!ft_strncmp(f->d_name, name, len) && ft_strcmp(f->d_name, ".")
					&& ft_strcmp(f->d_name, ".."))
			{
				ft_asprintf(&path, "%s/%s", dir_path, f->d_name);
				if (is_exec(path) == -1)
					ft_asprintf(&file_name, "%s/", f->d_name);
				else if (!(file_name = ft_strdup(f->d_name)))
					exit_prog(EXIT_FAILURE, "Malloc error.\n");
				ft_lstaddback(matches, ft_lstnew(file_name,
							sizeof(file_name)));
				ft_memdel((void **)&path);
			}
		closedir(dir);
	}
}

static char	*find_word(char *input, char **before, int *end)
{
	char	*word;
	char	*t;

	word = ft_strrchr(input, ' ');
	++word;
	*end = ft_strlen(word) - 1;
	t = *before;
	ft_asprintf(before, "%.*s", word - input, input);
	ft_memdel((void **)&t);
	while (*end >= 0 && word[*end] != '/')
		--(*end);
	return (word);
}

static int	comp_dyn(char *word, t_list **matches, char **before)
{
	char	*w;
	int		ret;
	size_t	len;

	ret = 0;
	len = ft_strlen(*before) - 1;
	w = *before;
	while (len && w[len] == ' ')
		--len;
	while (len && w[len] != ' ')
		--len;
	if (len)
		++len;
	if (!ft_strncmp(w + len, "env", 3) && (ret = 1))
		complete_first(matches, word, ft_strlen(word), before);
	else if ((!ft_strncmp(w + len, "setenv", 6)
				|| !ft_strncmp(w + len, "unsetenv", 8)
				|| !ft_strncmp(w + len, "read", 4)) && (ret = 1))
		comp_var(matches, word, ft_strlen(word), 1);
	else if (!ft_strncmp(w + len, "cd", 2) && (ret = 1))
		comp_dir(matches, word, ft_strlen(word), before);
	return (ret);
}

static void	end_second(char **before, int end, char *word, t_list **matches)
{
	char	*path;
	char	*tmp;

	path = NULL;
	ft_asprintf(&path, "%.*s", end + 1, word);
	word = word + end + 1;
	tmp = *before;
	*before = NULL;
	ft_asprintf(before, "%s%s", tmp, path);
	if (*path == '~')
		expand_home_in_comp(&path);
	find_file_in_directory(path, matches, word, ft_strlen(word));
	ft_memdel((void **)&tmp);
	ft_memdel((void **)&path);
}

void		complete_second(char *input, char **before, t_list **matches)
{
	int		end;
	char	*word;
	char	wd[MAXPATHLEN + 1];

	getcwd(wd, MAXPATHLEN + 1);
	word = find_word(input, before, &end);
	if (*word == '$')
		comp_var(matches, word, ft_strlen(word), 0);
	else if (comp_dyn(word, matches, before))
		return ;
	else if (end < 0)
		find_file_in_directory(wd, matches, word, ft_strlen(word));
	else
		end_second(before, end, word, matches);
}
