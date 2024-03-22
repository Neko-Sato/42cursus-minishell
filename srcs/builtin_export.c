/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:02:37 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/22 23:50:16 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "variable.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	internal(t_minishell *shell, char *word, int *status);
static int	export_noargs(t_minishell *shell);

int	builtin_export(t_minishell *shell, t_wordlist *wordlist)
{
	int	status;

	status = EXIT_SUCCESS;
	if (!wordlist)
		return (export_noargs(shell));
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

// static int	____(char *str)
// {
// 	return (!!ft_strpbrk(str, "<>&|()*\"~ "));
// }

static int	export_noargs(t_minishell *shell)
{
	int		err;
	size_t	i;

	err = 0;
	i = 0;
	while (i < shell->vars_len)
	{
		if (shell->vars[i]->attr & V_EXPORTED)
		{
			err = write(1, "export ", 7) == -1;
			err = err || write(1, shell->vars[i]->key,
					ft_strlen(shell->vars[i]->key)) == -1;
			if (shell->vars[i]->value)
			{
				err = err || write(1, "=", 1) == -1;
				err = err || write(1, shell->vars[i]->value,
						ft_strlen(shell->vars[i]->value)) == -1;
			}
			err = err || write(1, "\n", 1) == -1;
			if (err)
			{
				perror("minishell: export");
				return (EXIT_FAILURE);
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

// static int	export_noargs(t_minishell *shell)
// {
// 	int		ret;
// 	size_t	i;
// 	char	*key;
// 	char	*value;

// 	i = 0;
// 	while (shell->envp[i])
// 	{
// 		key = ft_strdup(shell->envp[i++]);
// 		if (!key)
// 			return (-1);
// 		value = ft_strchr(key, '=') + 1;
// 		// ret = show_var(key, value);
// 		(void)value;
// 		ret  = 0;
// 		free(key);
// 		if (ret)
// 			return (ret);
// 	}
// 	return (EXIT_SUCCESS);
// }

// static int show_var(char *key, char *value)
// {

// }

// static int	need_escape(char *str)
// {
// 	if (!*str)
// 		return (1);
// 	return (!!ft_strpbrk(str, "<>&|()*\"~ "));
// }

// static char	*escape(char *str)
// {
// 	char		*result;
// 	t_strgen	*strgen;

// 	strgen = ft_strgennew(STRGEN_BUUFERSIZE);
// 	if (!strgen)
// 		return (NULL);
// 	if (ft_strgenchr(strgen, '\''))
// 		result = ft_strgencomp(strgen);
// 	ft_strgendel(strgen);
// 	return (result);
// }

// static int	_print_environ(void)
// {
// }