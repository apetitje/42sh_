/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 17:26:54 by apetitje          #+#    #+#             */
/*   Updated: 2017/09/28 20:29:58 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static void		insert_glob(t_list *mtch, t_token **tok_tab,
		size_t *token_size, size_t *j)
{
	t_token	*end_tab;
	size_t	end_size;
	t_list	*tmp;

	end_size = 0;
	copy_tab(&end_tab, *tok_tab + *j + 1, &end_size, *token_size - *j - 1);
	ft_memdel((void **)&(*tok_tab)[*j].word);
	(*tok_tab)[*j].size = 0;
	(*tok_tab)[*j].type = 0;
	while (mtch)
	{
		(*tok_tab)[*j].word = mtch->data;
		if (!((*tok_tab)[*j].size = mtch->data_size))
			(*tok_tab)[*j].type = TOKEN_NULL;
		tmp = mtch;
		if ((mtch = mtch->next))
		{
			++(*j) && ++(*token_size);
			if (*token_size >= g_token_tab_size - 2)
				extend_tok_tab(tok_tab, &g_token_tab_size,
						g_token_tab_size * 2);
		}
		free(tmp);
	}
	copy_end_tab(&end_tab, end_size, *tok_tab + *j + 1);
}

static t_list	*multi_glob(char *word)
{
	char	**words;
	char	**tmp;
	t_list	*ret;
	t_list	*new;

	if (!(words = sh_split(word, " ", "''\"\"")))
		exit_prog(EXIT_FAILURE, "Malloc error (multi_glob)");
	tmp = words;
	ret = NULL;
	while (*tmp)
	{
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
	free(word);
	free(words);
	return (ret);
}

void			expand_glob(t_token **tok, size_t *token_size)
{
	size_t	i;
	size_t	j;
	t_list	*mtch;
	char	c;
	int		flag;

	j = 0;
	flag = 1;
	while (j < *token_size && !(i = 0))
	{
		while (flag && (*tok)[j].type != TOKEN_VOID && (j == 0
					|| (*tok)[j - 1].type != TOKEN_HEREDOC)
				&& (c = (*tok)[j].word[i++]))
			if (c == '{' || c == '[' || c == '*' || c == '?')
			{
				if ((mtch = multi_glob(ft_strdup((*tok)[j].word))))
				{
					insert_glob(mtch, tok, token_size, &j);
					flag = 0;
				}
			}
		++j;
		flag = 1;
	}
}
