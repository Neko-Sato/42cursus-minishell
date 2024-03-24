/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:50:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 20:05:04 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void	make_child_internal(t_minishell *shell, t_proc *proc, pid_t pid);

pid_t	make_child(t_minishell *shell)
{
	pid_t	pid;
	t_proc	*proc;

	proc = malloc(sizeof(t_proc));
	if (!proc)
		return (FATAL_ERR);
	pid = fork();
	if (pid <= 0)
	{
		free(proc);
		if (!pid)
		{
			shell->isinteractive = 0;
			signal(SIGQUIT, SIG_DFL);
		}
		else
		{
			perror("minishell: fork");
			return (SYSTEM_ERR);
		}
	}
	else
		make_child_internal(shell, proc, pid);
	return (pid);
}

static void	make_child_internal(t_minishell *shell, t_proc *proc, pid_t pid)
{
	t_proc	**temp;

	proc->next = NULL;
	proc->pid = pid;
	proc->status = -1;
	proc->running = 1;
	temp = &shell->pidlist;
	while (*temp)
		temp = &(*temp)->next;
	*temp = proc;
}
