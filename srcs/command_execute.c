/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:10:11 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/06 01:24:23 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "shell.h"
#include <unistd.h>

// int	execute_simplecom(t_simplecom *simplecom, t_heredoc *heredoc);
// int	execute_groupcom(t_groupcom *groupcom, t_heredoc *heredoc);
// int	execute_concom(t_conncom *conncom, t_heredoc *heredoc);

void	print_command(t_command *command, int level);

int	execute_command(t_minishell *shell)
{
	print_command(shell->command, 0);
	return (0);
}

// int	execute_command(t_command *command, t_heredoc *heredoc)
// {
// 	int	ret;

// 	if (command->type == CT_SIMPLE)
// 		ret = execute_simplecom(command->value.simplecom, heredoc);
// 	else if (command->type == CT_GROUP)
// 		ret = execute_groupcom(command->value.groupcom, heredoc);
// 	else if (command->type == CT_CONNCOM)
// 		ret = execute_concom(command->value.conncom, heredoc);
// 	return (ret);
// }

// int	execute_simplecom(t_simplecom *simplecom, t_heredoc *heredoc)
// {
// }

// int	execute_groupcom(t_groupcom *groupcom, t_heredoc *heredoc)
// {
// 	return (execute_command(groupcom->command, heredoc));
// }

// int	execute_concom(t_conncom *conncom, t_heredoc *heredoc)
// {
// 	int status[2];
// }