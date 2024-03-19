/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:26:31 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 18:41:38 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "execute.h"
#include "shell.h"
#include <libft.h>
#include <stdlib.h>

static int	execute_builtin_internal(t_minishell *shell, t_wordlist *wordlist);

int	execute_builtin(t_minishell *shell, t_execute_simple vars)
{
	int	status;

	if (!vars.already_fork && save_stdio(shell))
		return (-1);
	status = do_redirect(shell, vars.redirect);
	if (status == -1)
		return (-1);
	close_fds(vars.vars->fds_to_close_size, vars.vars->fds_to_close);
	if (!status)
		status = execute_builtin_internal(shell, vars.wordlist);
	if (vars.already_fork)
		exit(status);
	if (adapt_stdio(shell))
		return (-1);
	shell->last_status = status;
	return (status);
}

static int	execute_builtin_internal(t_minishell *shell, t_wordlist *wordlist)
{
	int	status;

	status = EXIT_FAILURE;
	if (!ft_strcmp(wordlist->word, "echo"))
		status = builtin_echo(shell, wordlist);
	else if (!ft_strcmp(wordlist->word, "env"))
		status = builtin_env(shell, wordlist);
	else if (!ft_strcmp(wordlist->word, "cd"))
		status = builtin_cd(shell, wordlist);
	else if (!ft_strcmp(wordlist->word, "pwd"))
		status = builtin_pwd(shell, wordlist);
	else if (!ft_strcmp(wordlist->word, "export"))
		status = builtin_export(shell, wordlist);
	else if (!ft_strcmp(wordlist->word, "unset"))
		status = builtin_unset(shell, wordlist);
	else if (!ft_strcmp(wordlist->word, "exit"))
		status = builtin_exit(shell, wordlist);
	return (status);
}

int	isbuiltin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
