/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:10:11 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/14 00:25:52 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "execute.h"
#include "shell.h"

static int	execute_groupcom(t_minishell *shell, t_groupcom *groupcom,
				int pipe_in, int pipe_out);
static int	execute_conncom(t_minishell *shell, t_conncom *command, int pipe_in,
				int pipe_out);

int	execute_command(t_minishell *shell, t_command *command)
{
	return (execute_command_internal(shell, command, -1, -1));
}

int	execute_command_internal(t_minishell *shell, t_command *command,
		int pipe_in, int pipe_out)
{
	int	status;

	status = 0;
	if (!command)
		;
	else if (command->type == CT_SIMPLE)
		status = execute_simplecom(shell, command->value.simplecom, pipe_in,
				pipe_out);
	else if (command->type == CT_GROUP)
		status = execute_groupcom(shell, command->value.groupcom, pipe_in,
				pipe_out);
	else if (command->type == CT_CONNCOM)
	{
		if (command->value.conncom->type == CCT_PIPE)
			status = execute_pipeline(shell, command, pipe_in, pipe_out);
		else
			status = execute_conncom(shell, command->value.conncom, pipe_in,
					pipe_out);
	}
	return (status);
}

static int	execute_groupcom(t_minishell *shell, t_groupcom *groupcom,
		int pipe_in, int pipe_out)
{
	return (execute_command_internal(shell, groupcom->command, pipe_in,
			pipe_out));
}

static int	execute_conncom(t_minishell *shell, t_conncom *conncom, int pipe_in,
		int pipe_out)
{
	int	status;

	status = 0;
	if (conncom->type == CCT_AND)
	{
		status = execute_command_internal(
				shell, conncom->command1, pipe_in, pipe_out);
		if (status != -1 && !shell->last_status)
			status = execute_command_internal(
					shell, conncom->command2, pipe_in, pipe_out);
	}
	else if (conncom->type == CCT_OR)
	{
		status = execute_command_internal(
				shell, conncom->command1, pipe_in, pipe_out);
		if (status != -1 && shell->last_status)
			status = execute_command_internal(
					shell, conncom->command2, pipe_in, pipe_out);
	}
	return (status);
}
