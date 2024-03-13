/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:10:11 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/13 11:40:50 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "execute.h"
#include "shell.h"
#include <unistd.h>

static int	execute_pipeline_internal(t_minishell *shell, t_command *command,
				int prev, int fildes[2]);

int	execute_pipeline(t_minishell *shell, t_command *command, int pipe_fd[2])
{
	int	status;
	int	prev;
	int	fildes[2];

	prev = pipe_fd[0];
	while (command->type == CT_CONNCOM
		&& command->value.conncom->type == CCT_PIPE)
	{
		status = execute_pipeline_internal(shell, command, prev, fildes);
		if (prev != pipe_fd[0])
			close(prev);
		if (status == -1)
			return (-1);
		prev = fildes[0];
		command = command->value.conncom->command2;
	}
	status = execute_command_internal(
			shell, command, (int []){prev, pipe_fd[1]});
	close(prev);
	return (status);
}

static int	execute_pipeline_internal(t_minishell *shell, t_command *command,
		int prev, int fildes[2])

{
	int	status;

	if (pipe(fildes))
		return (-1);
	status = execute_command_internal(
			shell, command->value.conncom->command1, (int []){prev, fildes[1]});
	close(fildes[1]);
	if (status == -1)
		close(fildes[0]);
	return (status);
}
