/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:10:11 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/14 20:29:19 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <stdio.h>

int	execute_simplecom(t_simplecom *simplecom, t_heredoc *heredoc);
int	execute_groupcom(t_groupcom *groupcom, t_heredoc *heredoc);
int	execute_concom(t_conncom *conncom, t_heredoc *heredoc);

int	execute_command(t_command *command, t_heredoc *heredoc)
{
	int	ret;

	if (command->type == CT_SIMPLE)
		ret = execute_simplecom(command->value.simplecom, heredoc);
	else if (command->type == CT_GROUP)
		ret = execute_groupcom(command->value.groupcom, heredoc);
	else if (command->type == CT_CONNCOM)
		ret = execute_concom(command->value.conncom, heredoc);
	return (ret);
}

int	execute_simplecom(t_simplecom *simplecom, t_heredoc *heredoc)
{

}

int	execute_groupcom(t_groupcom *groupcom, t_heredoc *heredoc)
{
	return (execute_command(groupcom->command, heredoc));
}

int	execute_concom(t_conncom *conncom, t_heredoc *heredoc)
{
	int	status[2];


}