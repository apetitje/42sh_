/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 15:47:24 by apetitje          #+#    #+#             */
/*   Updated: 2017/06/19 18:32:39 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	conf_save(t_infos *infos)
{
	if (tcgetattr(0, &infos->term) == -1)
		return (1);
	infos->old_conf = infos->term;
	infos->term.c_lflag &= ~(ICANON | ECHO | ISIG);
	infos->term.c_cc[VMIN] = 1;
	infos->term.c_cc[VTIME] = 0;
	return (0);
}

int			term_conf(t_infos *infos, int code)
{
	char		*name;
	int			ret;

	if (code == 1)
	{
		name = getenv("TERM");
		if (name == NULL)
			name = "vt100";
		if ((ret = tgetent(NULL, name)) < 0)
			return (ft_dprintf(2, "Could not access the termcap database.\n"));
		if (ret == 0)
			return (ft_dprintf(2, "Terminal type %s is not defined.\n", name));
		if (conf_save(infos))
			return (1);
	}
	else
		infos->term = infos->old_conf;
	ret = tcsetattr(0, TCSADRAIN, &infos->term);
	if (ret == -1)
		return (1);
	return (0);
}
