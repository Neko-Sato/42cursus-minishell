/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:10:11 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/30 03:25:39 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "execute.h"
#include "shell.h"
#include <stdio.h>
#include <unistd.h>

static int	execute_pipeline_internal(t_minishell *shell,
				t_command *command, int fildes[3]);

int	execute_pipeline(t_minishell *shell, t_command *command, t_execute vars)
{
	int	status;
	int	fildes[3];

	fildes[0] = vars.pipe_in;
	while (command->type == CT_CONNCOM
		&& command->value.conncom->type == CCT_PIPE)
	{
		status = execute_pipeline_internal(shell, command, fildes);
		if (fildes[0] != vars.pipe_in)
			close(fildes[0]);
		if (status < 0 && !shell->exit_immediately)
			return (status);
		fildes[0] = fildes[1];
		command = command->value.conncom->command2;
	}
	status = execute_command_internal(shell, command, (t_execute){
			fildes[0], vars.pipe_out,
			vars.fds_to_close_size, vars.fds_to_close});
	close(fildes[0]);
	return (status);
}

static int	execute_pipeline_internal(t_minishell *shell,
				t_command *command, int fildes[3])
{
	int	status;

	if (pipe(&fildes[1]))
	{
		perror("minishell: pipe");
		return (SYSTEM_ERR);
	}
	status = execute_command_internal(shell, command->value.conncom->command1,
			(t_execute){fildes[0], fildes[2], 1, (int []){fildes[1]}});
	close(fildes[2]);
	if (status < 0 && !shell->exit_immediately)
		close(fildes[1]);
	return (status);
}
