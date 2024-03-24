/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:25:38 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 16:42:49 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "parser.h"
#include "shell.h"
#include <libft.h>
#include <errno.h>
#include <stdio.h>
#include <readline.h>
#include <stdlib.h>
#include <unistd.h>

static int	reader_loop_internal(t_minishell *shell);

int	reader_loop(t_minishell *shell)
{
	int	status;

	status = NOERR;
	if (shell->isinteractive && set_signal())
		status = FATAL_ERR;
	if (!status)
		status = reader_loop_internal(shell);
	if (status == FATAL_ERR)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	if (shell->isinteractive)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	return (status);
}

static int	reader_loop_internal(t_minishell *shell)
{
	int	ret;

	while (!shell->eof_reached)
	{
		ret = read_command(shell);
		if (!ret)
			ret = execute_command(shell, shell->command);
		dispose_command(shell->command);
		shell->command = NULL;
		dispose_heredoc(shell->heredoc);
		shell->heredoc = NULL;
		cleanup_dead_jobs(shell);
		if (ret == FATAL_ERR)
			return (FATAL_ERR);
		else if (ret == SYSTEM_ERR)
			shell->last_status = EXIT_FAILURE;
		else if (!shell->isinteractive && ret == SYNTAX_ERR)
			break ;
	}
	return (shell->last_status);
}

int	shell_init(t_minishell *shell, char *envp[])
{
	ft_bzero(shell, sizeof(t_minishell));
	shell->cwd = getcwd(NULL, 0);
	if (!shell->cwd && errno != ENOENT)
		return (FATAL_ERR);
	shell->vars = ft_vector(sizeof(t_var *), NULL, 0);
	if (!shell->vars || init_variable(shell, envp))
	{
		shell_deinit(shell);
		return (FATAL_ERR);
	}
	shell->isinteractive = isatty(STDIN_FILENO) && isatty(STDERR_FILENO);
	ft_memset(shell->save_stdio, -1, sizeof(shell->save_stdio));
	if (shell->isinteractive)
		rl_event_hook = (void *)ft_noop;
	rl_instream = stdin;
	rl_outstream = stderr;
	return (NOERR);
}

void	shell_deinit(t_minishell *shell)
{
	size_t	i;
	t_proc	*temp;

	free(shell->cwd);
	while (shell->pidlist)
	{
		temp = shell->pidlist;
		shell->pidlist = shell->pidlist->next;
		free(temp);
	}
	i = 0;
	while (i < shell->vars_len)
		dispose_variable(shell->vars[i++]);
	ft_vector_del(shell->vars);
}

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
		if (envp[i++][key_len] == '=')
		{
			temp = ft_strdup(envp[i - 1]);
			if (!temp)
				return (FATAL_ERR);
			temp[key_len] = '\0';
			var = bind_variable(shell, temp, &temp[key_len + 1], 0);
			free(temp);
			if (!var)
				return (FATAL_ERR);
			var->attr |= V_EXPORTED;
		}
	}
	if (set_var_attribute(shell, "OLDPWD", V_EXPORTED, 0))
		return (FATAL_ERR);
	return (NOERR);
}
