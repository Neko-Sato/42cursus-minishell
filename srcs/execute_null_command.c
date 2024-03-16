/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_null_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:05:31 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/16 11:15:50 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	execute_null_command(t_minishell *shell, t_execute vars)
{
	if (!vars.already_fork && save_stdio(shell))
		return (-1);
	if (do_redirect(shell, vars.redirect))
		return (-1);
	if (vars.already_fork)
		exit(EXIT_SUCCESS);
	if (adapt_stdio(shell))
		return (-1);
	return (EXIT_SUCCESS);
}
