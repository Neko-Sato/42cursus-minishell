/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:44:40 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/22 17:08:50 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "variable.h"
#include <libft.h>
#include <stdlib.h>

int	init_variable(t_minishell *shell, char *envp[])
{
	size_t	i;
	char	*temp;
	size_t	key_len;
	t_var	*var;

	i = 0;
	while (envp[i])
	{
		key_len = ft_strcspn(envp[i], "=");
		if (envp[i][key_len] == '=')
		{
			temp = ft_strdup(envp[i]);
			if (!temp)
				return (-1);
			temp[key_len] = '\0';
			var = bind_variable(shell, temp, &temp[key_len + 1], 0);
			free(temp);
			if (!var)
				return (-1);
			var->attr |= V_EXPORTED;
		}
		i++;
	}
	return (0);
}

t_var	*find_variable(t_minishell *shell, char *key)
{
	size_t	i;

	i = 0;
	while (i < shell->vars_len)
	{
		if (!ft_strcmp(shell->vars[i]->key, key))
			return (shell->vars[i]);
		i++;
	}
	return (NULL);
}

char	*get_string_value(t_minishell *shell, char *key)
{
	t_var	*var;

	var = find_variable(shell, key);
	if (!var)
		return (NULL);
	return (var->value);
}

int	do_assignment(t_minishell *shell, char *word)
{
	char	*temp;
	size_t	key_len;
	int		flag;
	int		append;

	flag = 0;
	key_len = ft_strcspn(word, "=");
	if (word[key_len] != '=')
		return (0);
	temp = ft_strdup(word);
	if (!temp)
		return (-1);
	append = temp[key_len - 1] == '+';
	temp[key_len - append] = '\0';
	if (append)
		flag |= ASS_APPEND;
	if (!bind_variable(shell, temp, &temp[key_len + 1], flag))
	{
		free(temp);
		return (-1);
	}
	free(temp);
	return (0);
}
