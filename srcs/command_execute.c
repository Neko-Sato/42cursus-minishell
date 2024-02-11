/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:10:11 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/11 12:14:55 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

int	execute_command(t_command *command, t_heredoc *heredoc)
{
	int	ret;

	if (command->type == CT_SIMPLE)
		ret = execute_simplecom();
	else if (command->type == CT_GROUP)
		ret = execute_groupcom();
	else if (command->type == CT_CONNCOM)
		ret = execute_concom();
	return (ret);
}
