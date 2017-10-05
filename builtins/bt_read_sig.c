/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_read_sig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 13:57:44 by oyagci            #+#    #+#             */
/*   Updated: 2017/10/04 09:50:34 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	sigaction_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	read_set_sigint(void)
{
	struct sigaction sa;

	sa.sa_mask = 0;
	sa.sa_handler = sigaction_sigint;
	sa.sa_flags = SA_RESETHAND;
	sigaction(SIGINT, &sa, NULL);
}

void	read_set_signals(t_read_opt *opt)
{
	set_alrm();
	read_set_sigint();
	ft_alarm(opt->timeout);
}

char	*ft_stradd(char *s1, char *s2)
{
	char *new;

	if (!(new = ft_strjoin(s1, s2)))
		return (NULL);
	free(s1);
	return (new);
}
