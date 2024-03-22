/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:44:40 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/22 12:47:39 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "variable.h"
#include <libft.h>
#include <stdlib.h>

static size_t	get_exported_len(t_minishell *shell);
static char		*variable_string(char *key, char *value);

char	**get_envp(t_minishell *shell)
{
	size_t	i;
	char	**envp;

	envp = malloc(sizeof(char *) * (get_exported_len(shell) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (i < shell->vars_len)
	{
		if (shell->vars[i]->attr & V_EXPORTED && shell->vars[i]->value)
		{
			envp[i] = variable_string(shell->vars[i]->key,
					shell->vars[i]->value);
			if (!envp[i])
			{
				ft_2darraydel(envp);
				return (NULL);
			}
		}
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

static size_t	get_exported_len(t_minishell *shell)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	while (i < shell->vars_len)
	{
		if (shell->vars[i]->attr & V_EXPORTED && shell->vars[i]->value)
			len++;
		i++;
	}
	return (len);
}

static char	*variable_string(char *key, char *value)
{
	char	*result;
	size_t	size;

	size = ft_strlen(key) + ft_strlen(value) + 2;
	result = malloc(size);
	if (!result)
		return (NULL);
	ft_strlcpy(result, key, size);
	ft_strlcat(result, "=", size);
	ft_strlcat(result, value, size);
	return (result);
}
