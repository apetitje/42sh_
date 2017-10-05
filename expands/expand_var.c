/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:47:28 by apetitje          #+#    #+#             */
/*   Updated: 2017/09/29 13:49:49 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static void		replace_var(size_t *i, char **word)
{
	t_list	*p;
	char	*tmp;
	char	flag;

	p = g_env;
	--(*i);
	flag = 0;
	while (p)
	{
		if (!ft_strcmp(*word, get_var(p)))
		{
			ft_memdel((void **)word);
			if ((tmp = get_content(p)) && tmp[0] != '\0')
			{
				if (!(*word = ft_strdup(get_content(p))))
					exit_prog(EXIT_FAILURE, "Malloc error\n");
				*i += ft_strlen(get_content(p));
			}
			return ;
		}
		p = p->next;
		if (!p && !flag && ++flag)
			p = g_locales;
	}
	ft_memdel((void **)word);
}

static int		init_exp(char **word, char **begin, char **end,
		char *input)
{
	int		len;

	*word = NULL;
	*begin = NULL;
	*end = NULL;
	len = 0;
	while (input[len] && (ft_isdigit(input[len])
				|| ft_isalpha(input[len]) || input[len] == '_'
				|| input[len] == '?'))
		++len;
	return (len);
}

static int		free_and_return(char **word, char **begin, char **end, int ret)
{
	ft_memdel((void **)word);
	ft_memdel((void **)begin);
	ft_memdel((void **)end);
	return (ret);
}

int				expand_var(t_token *tok_tab, char *input, size_t *i, size_t *j)
{
	char	*word;
	int		len;
	char	*begin;
	char	*end;

	if (!input[++(*i)] || !(len = init_exp(&word, &begin, &end, input + *i)))
		return (0);
	if (*j == 0 || tok_tab[*j - 1].type != TOKEN_HEREDOC)
		ft_asprintf(&end, "%s", input + *i + len);
	else if (!(end = ft_strdup("")))
		exit_prog(EXIT_FAILURE, "Malloc error (expand_var)\n");
	ft_asprintf(&word, "%.*s", len, input + *i);
	ft_asprintf(&begin, "%.*s", *i - 1, tok_tab[*j].word);
	ft_memdel((void **)&tok_tab[*j].word);
	replace_var(i, &word);
	tok_tab[*j].size = ft_asprintf(&tok_tab[*j].word,
						"%s%s%s", begin, word, end);
	if (*j == 0 || tok_tab[*j - 1].type != TOKEN_HEREDOC)
	{
		if (!tok_tab[*j].size)
			tok_tab[*j].type = TOKEN_VOID;
		else
			tok_tab[*j].type = TOKEN_VAR_EXP;
	}
	return (free_and_return(&word, &begin, &end, (tok_tab[*j].size) ? 0 : 1));
}
