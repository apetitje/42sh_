/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 20:39:39 by apetitje          #+#    #+#             */
/*   Updated: 2017/09/28 20:29:16 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void	exit_handler(int sig)
{
	exit(sig);
}

void	handler(int sig)
{
	term_conf(&g_infos, 2);
	ft_dprintf(2, "\n[%d] Shell exited with status %d.\n", g_shellpid, sig);
	exit(sig);
}
