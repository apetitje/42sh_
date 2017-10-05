/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_access.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 15:56:43 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/05 00:46:41 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			open_hist(int flags1, int flags2)
{
	t_passwd	*passwd;
	char		*path;
	int			fd;

	path = NULL;
	passwd = getpwuid(getuid());
	ft_asprintf(&path, "%s/.sh_history.hist", passwd->pw_dir);
	if (flags2)
		fd = open(path, flags1, flags2);
	else
		fd = open(path, flags1);
	ft_memdel((void **)&path);
	return (fd);
}

void		erase_last(t_list **hist)
{
	t_list *p;

	p = *hist;
	while (p && p->next && p->next->next)
		p = p->next;
	free_hist(&p->next);
}

void		add_hist(t_list **hist, char *line, int count)
{
	t_hist	*new;
	t_list	*add;

	if (!line)
		return ;
	if (count >= 1000)
		erase_last(hist);
	if (!(new = malloc(sizeof(t_hist))))
		exit_prog(EXIT_FAILURE, "Malloc error.\n");
	if (!(new->content = ft_strdup(line)))
		exit_prog(EXIT_FAILURE, "Malloc error.\n");
	new->select = 0;
	if (!(add = ft_lstnew(new, sizeof(new))))
		exit_prog(EXIT_FAILURE, "Malloc error.\n");
	ft_lstadd(hist, add);
}
