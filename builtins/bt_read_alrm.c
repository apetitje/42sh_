/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_read_alrm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 17:16:36 by oyagci            #+#    #+#             */
/*   Updated: 2017/09/25 17:18:42 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"
#include <sys/time.h>

void			read_alrm(int sig, siginfo_t *siginfo, void *context)
{
	(void)sig;
	(void)siginfo;
	(void)context;
	g_prompt_size = 3;
}

unsigned int	ft_alarm(unsigned int seconds)
{
	struct itimerval old;
	struct itimerval new;

	new.it_interval.tv_usec = 0;
	new.it_interval.tv_sec = 0;
	new.it_value.tv_usec = 0;
	new.it_value.tv_sec = (long int)seconds;
	if (setitimer(ITIMER_REAL, &new, &old) < 0)
		return (0);
	else
		return (old.it_value.tv_sec);
}

void			set_alrm(void)
{
	struct sigaction act;

	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_sigaction = read_alrm;
	act.sa_flags = SA_RESETHAND;
	sigaction(SIGALRM, &act, NULL);
}
