/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_bind.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:44:40 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 12:58:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "variable.h"
#include <libft.h>
#include <stdlib.h>

static int	set_value(t_var *var, char *value, int flag);

t_var	*bind_variable(t_minishell *shell, char *key, char *value, int flag)
{
	t_var	*var;

	var = find_variable(shell, key);
	if (!var)
	{
		var = make_new_variable(key);
		if (!var)
			return (NULL);
		if (ft_vector_push_back(&shell->vars, &var))
		{
			dispose_variable(var);
			return (NULL);
		}
		shell->vars_len++;
	}
	if (set_value(var, value, flag))
		return (NULL);
	return (var);
}

static int	set_value(t_var *var, char *value, int flag)
{
	if (value)
	{
		if (flag & ASS_APPEND && var->value)
			value = ft_strjoin(var->value, value);
		else
			value = ft_strdup(value);
		if (!value)
			return (FATAL_ERR);
	}
	free(var->value);
	var->value = value;
	return (NOERR);
}

void	unbind_variable(t_minishell *shell, char *key)
{
	size_t	i;

	i = 0;
	while (i < shell->vars_len)
	{
		if (!ft_strcmp(shell->vars[i]->key, key))
			break ;
		i++;
	}
	if (i < shell->vars_len)
	{
		dispose_variable(shell->vars[i]);
		ft_vector_erase(shell->vars, i, 1);
		shell->vars_len--;
	}
}

t_var	*make_new_variable(char *key)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	ft_bzero(var, sizeof(t_var));
	var->key = ft_strdup(key);
	if (!var->key)
	{
		dispose_variable(var);
		return (NULL);
	}
	return (var);
}

void	dispose_variable(t_var *var)
{
	free(var->key);
	free(var->value);
	free(var);
}
