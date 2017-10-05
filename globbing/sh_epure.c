/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_epure.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 21:42:21 by clabouri          #+#    #+#             */
/*   Updated: 2017/09/18 08:52:22 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

int		sh_count_ep(char *word, char *del, char *escape)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	tmp2 = del;
	i = 0;
	while (*tmp2)
	{
		tmp = word;
		while ((tmp = sh_chr(tmp, *tmp2, "\"\"''")))
		{
			while (*(++tmp) && *tmp2 && *tmp != *tmp2)
				i += (ft_strchr(escape, *tmp) != NULL);
		}
		tmp2++;
	}
	return (i + ft_strlen(word));
}

void	sh_rmbs(char *word)
{
	if (!word)
		return ;
	while (*word)
	{
		if (*word == '\\')
			ft_strcpy(word, word + 1);
		word++;
	}
}

char	*sh_escape(char *word, char *escape)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = word;
	while (*tmp)
		i += (ft_strchr(escape, *(tmp++)) != NULL);
	if (!(tmp = ft_strnew(ft_strlen(word) + i)))
		exit_prog(EXIT_FAILURE, "Malloc error (sh_escape)\n");
	ft_strcpy(tmp, word);
	word = tmp;
	while (*tmp)
		if (*tmp && ft_strchr(escape, *(tmp++)))
		{
			ft_memmove(tmp, tmp - 1, ft_strlen(tmp - 1));
			*(tmp - 1) = '\\';
			tmp++;
		}
	return (word);
}

void	sh_rmdoublons(t_list *lst)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!lst || !lst->next)
		return ;
	while (lst && (tmp = lst->next))
	{
		tmp2 = lst;
		while (tmp)
		{
			if (ft_strequ(tmp->data, lst->data))
			{
				tmp2->next = tmp->next;
				ft_lstfree_elem(&tmp);
				tmp = tmp2->next;
				continue ;
			}
			tmp2 = tmp;
			tmp = tmp->next;
		}
		lst = lst->next;
	}
}

void	*free_ret_null(void **p1, void **p2, void **p3, void **p4)
{
	if (p1)
		free(*p1);
	if (p2)
		free(*p2);
	if (p3)
		free(*p3);
	if (p4)
		free(*p4);
	return (NULL);
}
