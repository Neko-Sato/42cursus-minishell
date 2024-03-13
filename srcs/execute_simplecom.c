/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simplecom.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:13:45 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/13 18:06:31 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "execute.h"
#include "shell.h"
#include "subst.h"
#include <stdio.h>
#include <stdlib.h>

static int	execute_simplecom_finally(t_minishell *shell,
				t_execute_simplecom *vars);
static int	execute_simplecom_internal(t_minishell *shell,
				t_execute_simplecom *vars);

int	execute_simplecom(t_minishell *shell, t_simplecom *simplecom, int pipe_in,
		int pipe_out)
{
	pid_t	pid;
	int		do_fork;

	do_fork = pipe_in != -1 || pipe_out != -1;
	if (do_fork)
	{
		pid = make_child(shell);
		if (pid == -1)
			return (-1);
		else if (pid)
		{
			if (pipe_out == -1)
				return (wait_for(shell, pid));
			return (EXIT_SUCCESS);
		}
	}
	return (execute_simplecom_finally(shell, &(t_execute_simplecom){simplecom,
			pipe_in, pipe_out, do_fork}));
}

static int	execute_simplecom_finally(t_minishell *shell,
		t_execute_simplecom *vars)
{
	int	status;

	status = execute_simplecom_internal(shell, vars);
	if (!vars->already_fork)
		return (status);
	if (status == -1)
	{
		perror("minishell");
		status = EXIT_FAILURE;
	}
	exit(status);
}

static int	execute_simplecom_internal(t_minishell *shell,
										t_execute_simplecom *vars)
{
	int			status;
	t_wordlist	*wordlist;

	if (!vars->simplecom->wordlist)
		return (execute_null_command(shell, (t_execute){NULL,
				vars->simplecom->redirect, vars->pipe_in, vars->pipe_out, 0}));
	wordlist = expand_wordlist(shell, vars->simplecom->wordlist);
	if (!wordlist)
		return (-1);
	if (0)
		status = execute_builtin(shell, (t_execute){wordlist,
				vars->simplecom->redirect, vars->pipe_in, vars->pipe_out,
				vars->already_fork});
	else
		status = execute_disk_command(shell, (t_execute){wordlist,
				vars->simplecom->redirect, vars->pipe_in, vars->pipe_out,
				vars->already_fork});
	dispose_wordlist(wordlist);
	return (status);
}
