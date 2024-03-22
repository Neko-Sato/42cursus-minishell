/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_null_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:05:31 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/22 18:13:10 by hshimizu         ###   ########.fr       */
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
		return (-1);
	status = do_redirect(shell, vars.redirect);
	if (status == -1)
		return (-1);
	close_fds(vars.vars->fds_to_close_size, vars.vars->fds_to_close);
	if (vars.already_fork)
		exit(status);
	if (restore_stdio(shell))
		return (-1);
	shell->last_status = status;
	return (status);
}
