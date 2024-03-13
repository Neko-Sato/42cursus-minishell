/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simplecom.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:13:45 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/13 10:05:49 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "execute.h"
#include "shell.h"
#include "subst.h"
#include <stdio.h>
#include <stdlib.h>

static int	execute_simplecom_internal(t_minishell *shell, t_command *command,
				int pipe_fd[2], int already_fork);

int	execute_simplecom(t_minishell *shell, t_command *command, int pipe_fd[2])
{
	int	temp;
	int	do_fork;

	do_fork = pipe_fd[0] != -1 || pipe_fd[1] != -1;
	if (do_fork)
	{
		temp = make_child(shell);
		if (temp == -1)
			return (-1);
		else if (temp)
		{
			if (pipe_fd[1] == -1)
				return (wait_for(shell, temp));
			return (EXIT_SUCCESS);
		}
	}
	temp = execute_simplecom_internal(shell, command, pipe_fd, do_fork);
	if (!do_fork)
		return (temp);
	if (temp == -1)
	{
		perror("minishell");
		temp = EXIT_FAILURE;
	}
	exit(temp);
}

static int	execute_simplecom_internal(t_minishell *shell, t_command *command,
		int pipe_fd[2], int already_fork)
{
	int			status;
	t_wordlist	*wordlist;

	(void)pipe_fd;
	(void)already_fork;
	wordlist = expand_wordlist(shell, command->value.simplecom->wordlist);
	if (command->value.simplecom->wordlist && !wordlist)
		return (-1);
	dispose_wordlist(command->value.simplecom->wordlist);
	command->value.simplecom->wordlist = wordlist;
	if (!command->value.simplecom->wordlist)
		status = EXIT_SUCCESS;
	else if (0 /*built-in*/)
		status = 1; //
	else
		status = 0;//execute_disk_command(shell, command, pipe_fd, already_fork);
	shell->last_status = status;
	return (shell->last_status);
}
