/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:02:37 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/23 03:05:50 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "subst.h"
#include "variable.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	internal(t_minishell *shell, char *word, int *status);
static int	show_variable(t_minishell *shell);

int	builtin_export(t_minishell *shell, t_wordlist *wordlist)
{
	int	status;

	status = EXIT_SUCCESS;
	if (!wordlist)
		return (show_variable(shell));
	while (wordlist)
	{
		if (internal(shell, wordlist->word, &status))
			return (-1);
		wordlist = wordlist->next;
	}
	return (status);
}

static int	internal(t_minishell *shell, char *word, int *status)
{
	char	*temp;
	size_t	key_len;

	key_len = ft_strcspn(word, "=");
	if (word[key_len] == '=')
		key_len -= word[key_len - 1] == '+';
	temp = ft_strndup(word, key_len);
	if (legal_identifier(temp))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("unset: not a valid identifier: ", STDERR_FILENO);
		ft_putendl_fd(word, STDERR_FILENO);
		*status = EXIT_FAILURE;
	}
	else
	{
		if (do_assignment(shell, word) || set_var_attribute(shell, temp,
				V_EXPORTED, 0))
			*status = -1;
	}
	free(temp);
	return (-(*status == -1));
}

static int	show_variable_internal(t_var *var, int *err);

static int	show_variable(t_minishell *shell)
{
	int		err;
	size_t	i;

	i = 0;
	while (i < shell->vars_len)
	{
		if (shell->vars[i]->attr & V_EXPORTED)
			if (show_variable_internal(shell->vars[i], &err))
				return (-1);
		if (err)
			break ;
		i++;
	}
	if (err)
	{
		perror("minishell: export:");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	show_variable_internal(t_var *var, int *err)
{
	char	*temp;

	*err = write(1, "export ", 7) == -1;
	*err = *err || write(1, var->key, ft_strlen(var->key)) == -1;
	if (var->value)
	{
		*err = *err || write(1, "=", 1) == -1;
		temp = ansic_quote(var->value);
		if (!temp)
			return (-1);
		*err = *err || write(1, temp, ft_strlen(temp)) == -1;
		free(temp);
	}
	*err = *err || write(1, "\n", 1) == -1;
	return (0);
}
