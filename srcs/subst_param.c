/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 21:36:16 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/28 20:17:15 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>
#include <unistd.h>
#include <stdlib.h>

/*
	変数を取得する関数を追加する必要がある
*/

static char	*param_expand_variable(t_minishell *shell, char *string,
				size_t *sindex);

char	*param_expand(t_minishell *shell, char *string, size_t *sindex)
{
	char	*result;
	int		c;

	c = string[*sindex];
	if (c == '$')
	{
		result = ft_itoa(getpid());
		(*sindex)++;
	}
	else if (c == '?')
	{
		result = ft_itoa(shell->last_status);
		(*sindex)++;
	}
	else
		result = param_expand_variable(shell, string, sindex);
	return (result);
}

static char	*param_expand_variable(t_minishell *shell, char *string,
		size_t *sindex)
{
	char	*key;
	char	*value;
	int		c;
	size_t	start;

	(void)shell;
	start = *sindex;
	while (1)
	{
		c = string[*sindex];
		if (!(ft_isalnum(c) || c == '_'))
			break ;
		(*sindex)++;
	}
	if (start == *sindex)
		return (ft_strdup("$"));
	key = ft_substr(&string[*sindex], 0, *sindex - start);
	if (!key)
		return (NULL);
	value = ft_strdup("<pram>");
	free(key);
	return (value);
}
