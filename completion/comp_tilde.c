/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 20:29:03 by apetitje          #+#    #+#             */
/*   Updated: 2017/08/09 19:10:54 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "globales.h"

static char	*find_data(char *input, size_t k, char tmp[])
{
	char		*data;
	t_passwd	*passwd;

	passwd = NULL;
	data = NULL;
	if (!k)
	{
		if (!(data = search_var_in_env(g_env, "HOME")))
			passwd = getpwuid(getuid());
	}
	else if (k == 1 && (input[k] == '+' || input[k] == '-'))
	{
		if (input[k] == '+' && !(data = search_var_in_env(g_env, "PWD")))
			tmp[0] = '+';
		if (input[k] == '-' && !(data = search_var_in_env(g_env, "OLDPWD")))
			tmp[0] = '-';
	}
	else
	{
		if (k < 500)
			ft_memcpy(tmp, input + 1, k);
		passwd = getpwnam(tmp);
	}
	data = (passwd) ? passwd->pw_dir : data;
	return (data);
}

void		expand_home_in_comp(char **to_find)
{
	char		*data;
	char		tmp[500];
	char		*t2;
	char		*t3;
	size_t		k;

	k = 0;
	t3 = NULL;
	data = NULL;
	ft_bzero(tmp, 500);
	t2 = *to_find;
	while (t2[++k])
		if (t2[k] == ' ' || t2[k] == '/' || t2[k] == '\n' || t2[k] == '\t')
		{
			if (t2[k] == '/' && t2[k + 1])
				t3 = t2 + k + 1;
			break ;
		}
	if ((data = find_data(*to_find, k - 1, tmp)))
	{
		ft_asprintf(to_find, "%s/%s", data, t3);
		ft_memdel((void **)&t2);
	}
}
