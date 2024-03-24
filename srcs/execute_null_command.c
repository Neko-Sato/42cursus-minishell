/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_null_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:05:31 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 14:10:12 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	execute_null_command(t_minishell *shell, t_execute_simple vars)
{
	int	status;

	if (!vars.already_fork && save_stdio(shell))
		return (SYSTEM_ERR);
	status = do_redirect(shell, vars.redirect);
	if (status < 0)
		return (status);
	close_fds(vars.vars->fds_to_close_size, vars.vars->fds_to_close);
	if (vars.already_fork)
		exit(status);
	if (restore_stdio(shell))
		return (FATAL_ERR);
	shell->last_status = status;
	return (status);
}
