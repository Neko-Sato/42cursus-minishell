/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_disk_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:29:01 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/13 15:50:33 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "execute.h"
#include "shell.h"
#include "subst.h"
#include <stdio.h>
#include <stdlib.h>

int	execute_disk_command(t_minishell *shell, t_command *command, int pipe_fd[2],
		int already_fork)
{
}