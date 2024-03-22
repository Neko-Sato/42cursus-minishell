/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:44:40 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/22 23:44:09 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "variable.h"
#include <libft.h>
#include <stdlib.h>

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

int	legal_identifier(char *name)
{
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (1);
		name++;
	}
	return (0);
}

int	set_var_attribute(t_minishell *shell, char *name, int attr, int undo)
{
	t_var	*var;

	var = find_variable(shell, name);
	if (!var)
		var = bind_variable(shell, name, NULL, 0);
	if (!var)
		return (-1);
	if (undo)
		var->attr &= ~attr;
	else
		var->attr |= attr;
	return (0);
}
