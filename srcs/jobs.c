/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:50:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/08 11:34:07 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void	set_pid_status(t_minishell *shell, pid_t pid, int status);
static void	reap_zombie_children(t_minishell *shell);
static void	cleanup_dead_jobs(t_minishell *shell);

pid_t	make_child(t_minishell *shell)
{
	pid_t	pid;
	t_proc	**temp;
	t_proc	*proc;

	proc = malloc(sizeof(t_proc));
	if (!proc)
		return (-1);
	pid = fork();
	if (pid <= 0)
		free(proc);
	else if (pid)
	{
		proc->next = NULL;
		proc->pid = pid;
		proc->status = -1;
		proc->running = 1;
		temp = &shell->pidlist;
		while (*temp)
			temp = &(*temp)->next;
		*temp = proc;
		shell->last_pid = pid;
	}
	return (pid);
}

int	wait_for(t_minishell *shell, pid_t pid)
{
	pid_t	got_pid;
	int		status;

	while (1)
	{
		got_pid = waitpid(-1, &status, 0);
		if (0 < got_pid)
		{
			set_pid_status(shell, got_pid, status);
			if (got_pid == pid)
				break ;
		}
	}
	reap_zombie_children(shell);
	shell->last_status = status;
	cleanup_dead_jobs(shell);
	return (status);
}

static void	reap_zombie_children(t_minishell *shell)
{
	pid_t	got_pid;
	int		status;

	while (1)
	{
		got_pid = waitpid(-1, &status, WNOHANG);
		if (0 < got_pid)
			set_pid_status(shell, got_pid, status);
		else
			break ;
	}
}

static void	set_pid_status(t_minishell *shell, pid_t pid, int status)
{
	t_proc	**temp;

	temp = &shell->pidlist;
	while (*temp && (*temp)->pid != pid)
		temp = &(*temp)->next;
	if (!*temp)
		return ;
	(*temp)->running = 0;
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(status);
	(*temp)->status = status;
}

static void	cleanup_dead_jobs(t_minishell *shell)
{
	t_proc	**temp;
	t_proc	*proc;

	temp = &shell->pidlist;
	while (*temp)
	{
		if (!(*temp)->running)
		{
			proc = *temp;
			*temp = proc->next;
			free(proc);
		}
		else
			temp = &(*temp)->next;
	}
}
