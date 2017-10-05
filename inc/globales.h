/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globales.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 18:35:39 by apetitje          #+#    #+#             */
/*   Updated: 2017/09/28 16:51:56 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBALES_H
# define GLOBALES_H

int			g_bg;
int			g_exit_status;
int			g_interactive;
int			g_last_cmpl;
int			g_subsh_fd;
size_t		g_prompt_size;
size_t		g_token_tab_size;
char		*g_clipboard;
t_list		*g_env;
t_list		*g_locales;
t_list		*g_exported;
t_token		*g_tok_tab;
t_list		*g_hist;
t_ast		*g_root;
t_infos		g_infos;
t_hashtable	g_hash;
pid_t		g_shellpid;
t_job		*g_jobs;
t_job		*g_currjob;
t_sub		*g_prev_sub;

#endif
