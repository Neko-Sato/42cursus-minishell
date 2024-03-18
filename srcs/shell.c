/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:25:38 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 08:15:48 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "parser.h"
#include "shell.h"
#include <errno.h>
#include <libft.h>
#include <stdio.h>
#include <readline.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static int	reader_loop_internal(t_minishell *shell);
static void	signal_handler(int signal);

int			g_interrupt_state = 0;

int	reader_loop(t_minishell *shell)
{
	int					status;
	struct sigaction	act;

	act.sa_handler = signal_handler;
	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	status = 0;
	if (shell->isinteractive && sigaction(SIGINT, &act, NULL))
		status = -1;
	if (!status)
		status = reader_loop_internal(shell);
	if (shell->isinteractive && sigaction(SIGINT, NULL, NULL))
		status = -1;
	if (status < 0)
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
	int			ret;
	t_command	*command;

	while (!shell->eof_reached)
	{
		ret = read_command(shell);
		if (ret == NOERR)
		{
			command = shell->command;
			shell->command = NULL;
			if (execute_command(shell, command) < 0)
				ret = SYSTEM_ERR;
			dispose_command(command);
		}
		dispose_command(shell->command);
		shell->command = NULL;
		dispose_heredoc(shell->heredoc);
		shell->heredoc = NULL;
		if (ret == SYSTEM_ERR)
			return (EXIT_FAILURE);
		else if (!shell->isinteractive && ret == SYNTAX_ERR)
			break ;
	}
	return (shell->last_status);
}

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_interrupt_state = 1;
		rl_done = 1;
	}
}

int	shell_init(t_minishell *shell, char *envp[])
{
	size_t	i;

	ft_bzero(shell, sizeof(t_minishell));
	shell->pid = getpid();
	shell->envp = ft_vector(sizeof(char *), NULL, ft_arrylen((void *)envp) + 1);
	if (!shell->envp)
		return (-1);
	i = 0;
	while (envp[i])
	{
		shell->envp[i] = ft_strdup(envp[i]);
		if (!shell->envp[i++])
			return (-1);
	}
	shell->envp[i] = NULL;
	shell->isinteractive = isatty(STDIN_FILENO) && isatty(STDERR_FILENO);
	ft_memset(shell->save_stdio, -1, sizeof(shell->save_stdio));
	if (shell->isinteractive)
		rl_event_hook = (void *)ft_noop;
	rl_instream = stdin;
	rl_outstream = stderr;
	return (0);
}

void	shell_deinit(t_minishell *shell)
{
	size_t	i;
	t_proc	*temp;

	while (shell->pidlist)
	{
		temp = shell->pidlist;
		shell->pidlist = shell->pidlist->next;
		free(temp);
	}
	i = 0;
	while (shell->envp[i])
		free(shell->envp[i++]);
	ft_vector_del(shell->envp);
}
