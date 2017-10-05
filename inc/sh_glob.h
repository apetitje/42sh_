/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_glob.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 17:06:33 by clabouri          #+#    #+#             */
/*   Updated: 2017/09/24 18:17:06 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_GLOB_H
# define SH_GLOB_H
# include <dirent.h>
# include "sh42.h"

t_list			*sh_glob(char *word);
t_list			*sh_brace(char *word);
char			**sh_brcsplt(char *word);
char			**sh_build_exprs(char *word);
t_list			*sh_range(char *word);
t_list			*sh_handle_range(char *word, char *range, int rev);
t_list			*sh_wc_and_dot(char *word, char *path);
t_list			*sh_oc_in_path(char *word, char *path);
int				sh_match(char *s1, char *s2);
char			*sh_search_path(char *word, int kslash);

void			sh_rmdoublons(t_list *lst);
int				sh_count_ep(char *word, char *del, char *escape);
char			*sh_escape(char *word, char *escape);
void			sh_rmbs(char *word);
char			**sh_split(char *str, char *sep, char *jump);
char			*sh_chr(char *str, char c, char *jump);
char			*sh_rchr(char *str, char c, char *jump);
void			*free_ret_null(void **p1, void **p2, void **p3, void **p4);

#endif
