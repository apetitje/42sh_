/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_bt_spec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 22:47:50 by hanguelk          #+#    #+#             */
/*   Updated: 2017/10/03 22:57:58 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

int		resume_if_shellpgid(t_job *j)
{
	t_process	*p;
	pid_t		bk;
	int			stat;

	stat = 0;
	p = j->first;
	while (p)
	{
		bk = p->cpid;
		kill(bk, SIGCONT);
		p = p->next;
	}
	waitpid(bk, &stat, WUNTRACED);
	return (stat);
}
