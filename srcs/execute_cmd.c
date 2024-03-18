/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:10:11 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 01:26:39 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "execute.h"
#include "shell.h"

static int	execute_groupcom(t_minishell *shell,
				t_groupcom *groupcom, t_execute vars);
static int	execute_conncom(t_minishell *shell,
				t_conncom *command, t_execute vars);

int	execute_command(t_minishell *shell, t_command *command)
{
	return (execute_command_internal(shell,
			command, (t_execute){-1, -1, 0, NULL}));
}

int	execute_command_internal(t_minishell *shell,
		t_command *command, t_execute vars)
{
	int	status;

	status = 0;
	if (!command)
		;
	else if (command->type == CT_SIMPLE)
		status = execute_simplecom(shell, command->value.simplecom, vars);
	else if (command->type == CT_GROUP)
		status = execute_groupcom(shell, command->value.groupcom, vars);
	else if (command->type == CT_CONNCOM)
	{
		if (command->value.conncom->type == CCT_PIPE)
			status = execute_pipeline(shell, command, vars);
		else
			status = execute_conncom(shell, command->value.conncom, vars);
	}
	return (status);
}

static int	execute_groupcom(t_minishell *shell,
		t_groupcom *groupcom, t_execute vars)
{
	return (execute_command_internal(shell, groupcom->command, vars));
}

static int	execute_conncom(t_minishell *shell,
		t_conncom *conncom, t_execute vars)
{
	int	status;

	status = 0;
	if (conncom->type == CCT_AND)
	{
		status = execute_command_internal(
				shell, conncom->command1, vars);
		if (status != -1 && !shell->last_status)
			status = execute_command_internal(
					shell, conncom->command2, vars);
	}
	else if (conncom->type == CCT_OR)
	{
		status = execute_command_internal(
				shell, conncom->command1, vars);
		if (status != -1 && shell->last_status)
			status = execute_command_internal(
					shell, conncom->command2, vars);
	}
	return (status);
}
