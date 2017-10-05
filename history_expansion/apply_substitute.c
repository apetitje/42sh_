/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_subsitute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 11:06:37 by oyagci            #+#    #+#             */
/*   Updated: 2017/08/22 14:00:33 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void			insert_left(char *left, char **s, size_t i)
{
	char	*word;

	if (!(word = ft_strnew(ft_strlen(left) + ft_strlen(*s))))
		exit_prog(EXIT_FAILURE, "Malloc error (insert_left)\n");
	ft_strncpy(word, *s, i);
	ft_strcat(word, left);
	ft_strcat(word, *s + i + 1);
	free(*s);
	*s = word;
}

void			expand_ampersand(char *left, char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '&')
			insert_left(left, &s, i);
		i += 1;
	}
}

char			*replace_word(char *left, char *right, char *event, char *start)
{
	char	*s;

	s = ft_strnew((ft_strlen(event) - ft_strlen(left)) + ft_strlen(right));
	if (!s)
		return (NULL);
	ft_strncpy(s, event, start - event);
	ft_strcat(s, right);
	ft_strcat(s, start + ft_strlen(left));
	return (s);
}

void			save_sub(t_sub *sub)
{
	if (g_prev_sub == sub)
		return ;
	if (g_prev_sub)
		free_substitute(g_prev_sub);
	g_prev_sub = NULL;
	if (NULL == (g_prev_sub = ft_memalloc(sizeof(t_sub))))
		exit_prog(EXIT_FAILURE, "Malloc error (save_sub)\n");
	if (NULL == (g_prev_sub->left = ft_strdup(sub->left)))
		exit_prog(EXIT_FAILURE, "Malloc error (save_sub)\n");
	if (NULL == (g_prev_sub->right = ft_strdup(sub->right)))
		exit_prog(EXIT_FAILURE, "Malloc error (save_sub)\n");
}

int				apply_substitute(t_sub *sub, char **event, int global)
{
	char	*s;
	char	*tmp;

	if (!sub)
		return (0);
	save_sub(sub);
	expand_ampersand(sub->left, sub->right);
	if ((s = ft_strstr(*event, sub->left)))
	{
		if ((tmp = replace_word(sub->left, sub->right, *event, s)))
		{
			free(*event);
			*event = tmp;
		}
		if (global)
			apply_substitute(sub, event, global);
	}
	return (1);
}
