/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:10:11 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/13 11:39:57 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "execute.h"
#include "shell.h"

int	execute_command(t_minishell *shell, t_command *command)
{
	return (execute_command_internal(shell, command, (int []){-1, -1}));
}

int	execute_command_internal(t_minishell *shell, t_command *command,
		int pipe_fd[2])
{
	int	status;

	if (!command)
		status = 0;
	else if (command->type == CT_SIMPLE)
		status = execute_simplecom(shell, command, pipe_fd);
	else if (command->type == CT_GROUP)
		status = execute_groupcom(shell, command, pipe_fd);
	else if (command->type == CT_CONNCOM)
		status = execute_conncom(shell, command, pipe_fd);
	return (status);
}

int	execute_groupcom(t_minishell *shell, t_command *command, int pipe_fd[2])
{
	return (execute_command_internal(shell, command->value.groupcom->command,
			pipe_fd));
}

int	execute_conncom(t_minishell *shell, t_command *command, int pipe_fd[2])
{
	int	status;

	if (command->value.conncom->type == CCT_PIPE)
		status = execute_pipeline(shell, command, pipe_fd);
	else if (command->value.conncom->type == CCT_AND)
	{
		status = execute_command_internal(
				shell, command->value.conncom->command1, pipe_fd);
		if (status != -1 && !shell->last_status)
			status = execute_command_internal(
					shell, command->value.conncom->command2, pipe_fd);
	}
	else if (command->value.conncom->type == CCT_OR)
	{
		status = execute_command_internal(
				shell, command->value.conncom->command1, pipe_fd);
		if (status != -1 && shell->last_status)
			status = execute_command_internal(
					shell, command->value.conncom->command2, pipe_fd);
	}
	return (status);
}
