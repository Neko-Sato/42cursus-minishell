/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:25:38 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/24 04:11:19 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shell.h"
#include <errno.h>
#include <libft.h>
#include <readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	reader_loop_internal(t_minishell *shell);
static void	signal_handler(int signal);

int			g_interrupt_state = 0;

int	reader_loop(t_minishell *shell)
{
	int					status;
	struct sigaction	act;
	struct sigaction	oact;

	act.sa_handler = signal_handler;
	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	act.sa_restorer = NULL;
	status = 0;
	if (shell->isinteractive && sigaction(SIGINT, &act, &oact))
		status = -1;
	if (!status)
		status = reader_loop_internal(shell);
	if (shell->isinteractive && sigaction(SIGINT, &oact, NULL))
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
	int	ret;

	while (!shell->eof_reached)
	{
		ret = read_command(shell);
		if (ret == NOERR)
			ret = execute_command(shell);
		else if (ret == INTERRUPT)
			shell->last_status = 128 | SIGINT;
		else if (ret == SYSTEM_ERR)
			shell->last_status = 2;
		dispose_command(shell->command);
		shell->command = NULL;
		dispose_heredoc(shell->heredoc);
		shell->heredoc = NULL;
		if (ret == SYSTEM_ERR)
			return (EXIT_FAILURE);
		else if (!shell->isinteractive && ret == SYNTAX_ERR)
			return (2);
	}
	return (shell->last_status);
}

int	shell_init(t_minishell *shell, char *envp[])
{
	shell->envp = envp;
	shell->command = NULL;
	shell->heredoc = NULL;
	shell->isinteractive = isatty(STDIN_FILENO) && isatty(STDERR_FILENO);
	shell->last_status = 0;
	shell->string = NULL;
	shell->sindex = 0;
	shell->line = 0;
	shell->eof_reached = 0;
	if (shell->isinteractive)
		rl_event_hook = (void *)ft_noop;
	rl_instream = stdin;
	rl_outstream = stderr;
	return (0);
}

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_interrupt_state = 1;
		rl_done = 1;
	}
}
