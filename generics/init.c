/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 18:37:15 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/04 20:04:06 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

void	signal_init(void)
{
	signal(SIGQUIT, &handler);
	signal(SIGILL, &handler);
	signal(SIGABRT, &handler);
	signal(SIGFPE, &handler);
	signal(SIGBUS, &handler);
	signal(SIGSEGV, &handler);
	signal(SIGTERM, &handler);
	signal(SIGINT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	ignore_jobsignal();
}

void	init_vars(void)
{
	g_last_cmpl = 0;
	g_subsh_fd = 0;
	g_exit_status = 0;
	g_clipboard = NULL;
	g_token_tab_size = 100;
	g_hist = NULL;
	g_tok_tab = NULL;
	g_root = NULL;
	g_hash.nbbckt = 0;
	g_hash.table = NULL;
	g_shellpid = getpid();
	g_jobs = NULL;
	g_currjob = NULL;
	g_locales = NULL;
	init_tok_tab(&g_tok_tab, g_token_tab_size);
}

void	init_main(void)
{
	extern char	**environ;

	init_vars();
	signal_init();
	g_prompt_size = 3;
	g_env = env_list(environ);
}

void	read_hist(t_list **hist)
{
	int			fd;
	char		*line;
	int			ret;
	int			count;

	line = NULL;
	count = 0;
	fd = open_hist(O_RDONLY, 0);
	if (lseek(fd, -20000, SEEK_END) == -1)
		lseek(fd, 0, SEEK_SET);
	while (fd != -1 && (ret = get_next_line(fd, &line)) && ret != -1)
	{
		++count;
		add_hist(hist, line, count);
		ft_memdel((void **)&line);
	}
	ft_memdel((void **)&line);
	if (fd == -1 || ret == -1)
		*hist = NULL;
	if (fd != -1)
		close(fd);
}
