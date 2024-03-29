/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 21:36:16 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/23 15:52:25 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "variable.h"
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

static char	*param_expand_variable(t_minishell *shell, char *string,
				size_t *sindex);

char	*param_expand(t_minishell *shell, char *string, size_t *sindex)
{
	char	*result;
	int		c;

	c = string[*sindex];
	if (c == '?')
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
	char		*key;
	const char	*value;
	int			c;
	size_t		start;

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
	key = ft_substr(&string[start], 0, *sindex - start);
	if (!key)
		return (NULL);
	value = get_string_value(shell, key);
	if (!value)
		value = "";
	free(key);
	return (ft_strdup(value));
}
