/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 02:25:37 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/30 03:27:26 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execute.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <libft.h>

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

	while (!shell->eof_reached && !shell->exit_immediately)
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
