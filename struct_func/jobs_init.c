/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 17:50:19 by hanguelk          #+#    #+#             */
/*   Updated: 2017/10/04 18:31:28 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static t_job		*init_job(char *input, int index)
{
	t_job	*tmp;

	if (!(tmp = (t_job *)malloc(sizeof(t_job))))
		exit_prog(EXIT_FAILURE, "Malloc error");
	tmp->cmdline = (input) ? ft_strdup(input) : NULL;
	if (!tmp->cmdline && input)
		exit_prog(EXIT_FAILURE, "Malloc error");
	tmp->pgid = 0;
	tmp->active = 1;
	tmp->subsh = 0;
	tmp->first = NULL;
	tmp->next = NULL;
	tmp->ao = 0;
	tmp->bg = 0;
	tmp->code = 0;
	tmp->current = '+';
	tmp->notified = 0;
	tmp->pipeline = 0;
	tmp->bgnot = 0;
	tmp->index = index;
	return (tmp);
}

char				*recompute_cmd(t_command *args)
{
	char	*t1;
	char	*t2;
	size_t	i;

	if (args)
	{
		i = 0;
		if (!(t1 = ft_strnew(1)))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
		while (i < args->tok_size)
		{
			ft_asprintf(&t2, "%s %s", t1, args->tokens[i++].word);
			free(t1);
			t1 = t2;
		}
		return (t2);
	}
	return (NULL);
}

static t_process	*init_process(pid_t pid, t_command *args)
{
	t_process	*p;

	if (!(p = (t_process *)malloc(sizeof(t_process))))
		exit_prog(EXIT_FAILURE, "Malloc error");
	p->cpid = pid;
	p->stat = 0;
	p->pstat = 0;
	p->next = NULL;
	p->cmd = recompute_cmd(args);
	return (p);
}

void				process_add_to_job(t_job *j, pid_t pid, t_command *args,
		char *cmd)
{
	t_process	*tmp;
	t_process	*lst;

	tmp = init_process(pid, args);
	if (cmd)
	{
		if (!(tmp->cmd = ft_strdup(cmd)))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
	}
	else if (!tmp->cmd && j->cmdline)
	{
		if (!(tmp->cmd = ft_strdup(j->cmdline)))
			exit_prog(EXIT_FAILURE, "Malloc error\n");
	}
	lst = j->first;
	if (lst == NULL)
		j->first = tmp;
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = tmp;
	}
}

t_job				*job_add(t_job **j, char *input)
{
	t_job	*bk;
	t_job	*tmp;
	int		i;

	i = 1;
	tmp = init_job(input, i);
	if (*j == NULL)
		*j = tmp;
	else
	{
		bk = *j;
		while (++i && bk->next)
		{
			bk->current = ' ';
			bk = bk->next;
		}
		bk->current = '-';
		bk->next = tmp;
		tmp->index = bk->index + 1;
	}
	return (tmp);
}
