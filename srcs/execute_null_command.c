/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_null_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:05:31 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/13 19:04:36 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "shell.h"
#include <unistd.h>

int	execute_null_command(t_minishell *shell, t_execute vars)
{
	int	temp[2];

	while (1)
	{
		temp[0] = dup(STDIN_FILENO);
		if (temp[0] == -1)
			break ;
		temp[1] = dup(STDOUT_FILENO);
		if (temp[1] == -1)
			break ;
		if (do_redirect(shell, vars.redirect))
			break ;
		if (dup2(temp[0], STDIN_FILENO) == -1)
			break ;
		close(temp[0]);
		if (dup2(temp[1], STDOUT_FILENO) == -1)
			break ;
		close(temp[1]);
		return (0);
	}
	return (-1);
}
