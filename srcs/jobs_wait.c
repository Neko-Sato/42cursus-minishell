/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:50:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 21:46:27 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "shell.h"
#include <libft.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void	set_pid_status(t_minishell *shell, pid_t pid, int status);
static void	reap_zombie_children(t_minishell *shell);
static char	*str_signal(int signal);

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
		ft_putendl_fd(str_signal(WTERMSIG(status)), STDERR_FILENO);
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

static char	*str_signal(int n)
{
	if (65 < n || n < 1 || n == 32 || n == 33 || n == SIGINT)
		return ("");
	return ((char *[]){
		NULL, "Hangup", "Interrupt", "Quit", "Illegal instruction",
		"Trace/breakpoint trap", "Aborted", "Bus error",
		"Floating point exception", "Killed", "User defined signal 1",
		"Segmentation fault", "User defined signal 2", "Broken pipe",
		"Alarm clock", "Terminated", "Stack fault", "Child exited",
		"Continued", "Stopped (signal)", "Stopped", "Stopped (tty input)",
		"Stopped (tty output)", "Urgent I/O condition",
		"CPU time limit exceeded", "File size limit exceeded",
		"Virtual timer expired", "Profiling timer expired",
		"Window changed", "I/O possible", "Power failure",
		"Bad system call", NULL, NULL, "Real-time signal 0",
		"Real-time signal 1", "Real-time signal 2", "Real-time signal 3",
		"Real-time signal 4", "Real-time signal 5", "Real-time signal 6",
		"Real-time signal 7", "Real-time signal 8", "Real-time signal 9",
		"Real-time signal 10", "Real-time signal 11", "Real-time signal 12",
		"Real-time signal 13", "Real-time signal 14", "Real-time signal 15",
		"Real-time signal 16", "Real-time signal 17", "Real-time signal 18",
		"Real-time signal 19", "Real-time signal 20", "Real-time signal 21",
		"Real-time signal 22", "Real-time signal 23", "Real-time signal 24",
		"Real-time signal 25", "Real-time signal 26", "Real-time signal 27",
		"Real-time signal 28", "Real-time signal 29",
		"Real-time signal 30"}[n]);
}
