/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:50:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/28 20:37:30 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "shell.h"
#include <libft.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void			set_pid_status(t_minishell *shell, pid_t pid, int status);
static void			reap_zombie_children(t_minishell *shell);
static const char	*str_signal(int n);

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
	if (WIFSIGNALED(status))
		ft_putendl_fd((char *)str_signal(WTERMSIG(status)), STDERR_FILENO);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(status);
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
	(*temp)->status = status;
}

void	cleanup_dead_jobs(t_minishell *shell)
{
	t_proc	**temp;
	t_proc	*proc;

	reap_zombie_children(shell);
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

static const char	*str_signal(int n)
{
	if (65 < n || n < 1 || n == 2 || n == 32 || n == 33)
		return ("");
	return ((char *)sys_siglist[n]);
}
