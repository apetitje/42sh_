/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_history_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:23:59 by oyagci            #+#    #+#             */
/*   Updated: 2017/10/05 10:55:17 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int			get_hist_count(t_list *hist)
{
	int		count;

	count = 0;
	while (hist)
	{
		hist = hist->next;
		count += 1;
	}
	return (count);
}

int			print_expected(void)
{
	ft_dprintf(2, "history: expected numerical value\n");
	return (1);
}

int			history_usage(void)
{
	ft_dprintf(2,
		"history: usage: history [-c] [-d offset] [-arnw filename]\n");
	return (1);
}

int			history_read(t_hist_opt *opt)
{
	int		fd;
	char	*line;
	int		count;

	if (opt->value)
		fd = open(opt->value, O_RDONLY);
	else
		fd = open_hist(O_RDONLY, 0);
	if (lseek(fd, -20000, SEEK_END) == -1)
		lseek(fd, 0, SEEK_SET);
	if (-1 == fd)
		return (1);
	count = get_hist_count(g_hist);
	while (get_next_line(fd, &line) > 0)
	{
		add_hist(&g_hist, line, count);
		free(line);
	}
	free(line);
	close(fd);
	return (0);
}

int			write_history(t_hist_opt *opt)
{
	int		fd;
	t_list	*head;

	if (opt->value)
		fd = open(opt->value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open_hist(O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (1);
	head = g_hist;
	while (head && head->next)
	{
		ft_dprintf(fd, "%s\n", get_hist(head));
		head = head->next;
	}
	close(fd);
	return (0);
}
