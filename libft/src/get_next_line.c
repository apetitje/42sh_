/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 00:29:55 by clabouri          #+#    #+#             */
/*   Updated: 2017/10/05 15:22:54 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	read_line(const int fd, char **line, char (*cache)[])
{
	char			buff[BUFF_SIZE + 1];
	char			*endl;
	int				rd;
	int				ret;

	ret = 0;
	while ((rd = read(fd, buff, BUFF_SIZE)))
	{
		if ((ret = 1) && rd == -1)
			return (-1);
		buff[rd] = 0;
		if ((endl = ft_strchr(buff, '\n')))
		{
			!(*(endl++) = 0) && ft_strcpy(*cache, endl);
			if (!(*line = ft_strjoinfree(*line, buff, 1)))
				return (-1);
			return (1);
		}
		endl = *line;
		if (!(*line = ft_strjoinfree(*line, buff, 1)))
			return (-1);
	}
	(!ret) ? free(*line) : ret;
	*line = (!ret) ? NULL : *line;
	return (ret);
}

int			get_next_line(const int fd, char **line)
{
	static t_fd	cache[MAX_FD];
	char		*endl;

	if (fd < 0 || !line || !(*line = ft_strdup(cache[fd % MAX_FD].save)))
		return (-1);
	if ((endl = ft_strchr(*line, '\n')))
	{
		*(endl++) = 0;
		ft_strcpy(cache[fd % MAX_FD].save, endl);
		return (1);
	}
	ft_strclr(cache[fd % MAX_FD].save);
	if (!ft_strlen(*line))
		return (read_line(fd, line, &cache[fd % MAX_FD].save));
	if (read_line(fd, line, &cache[fd % MAX_FD].save) == -1)
	{
		free(*line);
		*line = NULL;
		return (-1);
	}
	return (1);
}
