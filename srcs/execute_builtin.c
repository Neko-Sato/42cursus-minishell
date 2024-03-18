/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:26:31 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 08:29:36 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "shell.h"
#include <stdlib.h>

int	execute_builtin(t_minishell *shell, t_execute_simple vars)
{
	(void)shell;
	if (vars.already_fork)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	isbuiltin(char *cmd)
{
	(void)cmd;
	return (0);
}
