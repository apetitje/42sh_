/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 12:25:27 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/05 12:44:35 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static int	manage_input(char **input)
{
	free_tok_tab_content(g_tok_tab);
	free_ast(g_root);
	g_root = NULL;
	if (parse_line(input, &g_tok_tab, &g_token_tab_size))
		return (1);
	if (check_grammar(g_tok_tab) || ast_construct(g_tok_tab, &g_root))
		return (1);
	g_currjob = job_add(&g_jobs, *input);
	if (ast_do_commands(g_root))
		return (1);
	return (0);
}

static int	non_interactive(void)
{
	char	*input;
	int		ret;

	input = NULL;
	ret = 0;
	while ((ret = get_next_line(0, &input)) && ret != -1)
	{
		if (manage_input(&input))
		{
			ft_memdel((void **)&input);
			return (1);
		}
		ft_memdel((void **)&input);
	}
	ft_memdel((void **)&input);
	free_all();
	if (ret == -1)
		return (1);
	return (0);
}

static int	interactive(void)
{
	char	*input;

	if ((input = read_line(&g_hist)) == NULL)
		return (0);
	if (manage_input(&input))
	{
		ft_memdel((void **)&input);
		return (1);
	}
	ft_memdel((void **)&input);
	return (0);
}

int			main(void)
{
	extern char	**environ;

	init_main();
	update_shlvl(&g_env);
	if ((g_interactive = isatty(0)) == 0)
	{
		non_interactive();
		return (g_exit_status);
	}
	else
	{
		if (tcgetpgrp(0) != getpgrp())
			kill(-g_shellpid, SIGSTOP);
		setpgid(g_shellpid, g_shellpid);
		tcsetpgrp(0, g_shellpid);
		read_hist(&g_hist);
		while (1)
		{
			interactive();
			wait_nonblock();
			update_jobs_stat();
			g_currjob = NULL;
		}
	}
	return (0);
}
