/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:10:11 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/08 11:40:48 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "shell.h"
#include "subst.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
	フォークしたら　プロセスのリストに追加する
	execute_command_internal
	の最後で最後にwaitしたpidが来るまでwaitする
	パイプよりもRedirectのほうが強い

	pipelineはその関数の中でmake_child(fork)をする、
	つまりは、simplecomがforkを必要とするかの区別がいる

	statuscodeの取得は全部last_statusで行う、
	でも明らかな場合は返り値にもする
	systemerrの時用
*/

void	print_wordlist(t_wordlist *wordlist, int level);

int		execute_command_internal(t_minishell *shell, t_command *command,
			int pipe_fd[2]);
int		execute_simplecom(t_minishell *shell, t_command *command,
			int pipe_fd[2]);
int		execute_pipeline(t_minishell *shell, t_command *command,
			int pipe_fd[2]);

int	execute_command(t_minishell *shell, t_command *command)
{
	int	pipe_fd[2];

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	return (execute_command_internal(shell, command, pipe_fd));
}

int	execute_command_internal(t_minishell *shell, t_command *command,
		int pipe_fd[2])
{
	int	status;

	if (!command)
		return (0);
	if (command->type == CT_SIMPLE)
		status = execute_simplecom(shell, command, pipe_fd);
	else if (command->type == CT_GROUP)
		status = execute_command_internal(shell, command, pipe_fd);
	else if (command->type == CT_CONNCOM)
	{
		if (command->value.conncom->type == CCT_PIPE)
			status = execute_pipeline(shell, command, pipe_fd);
		else
		{
			status = execute_command_internal(
				shell, command->value.conncom->command1, pipe_fd);
			if (!shell->last_status == (command->value.conncom->type == CCT_AND))
				status = execute_command_internal(
					shell, command->value.conncom->command2, pipe_fd);
		}
	}
	return (status);
}

//asyncがTrueの時実行時フォークしない
int	execute_simplecom(t_minishell *shell, t_command *command, int pipe_fd[2])
{
	t_wordlist	*word;
	char		**temp;
	int			async;
	pid_t		pid;

	async = 0 < pipe_fd[0] || 0 < pipe_fd[1];
	if (async)
	{
		pid = make_child(shell);
		if (pid < 0)
			return (-1);
		else if (pid)
			return (0);
	}
	word = expand_wordlist(shell, command->value.simplecom->wordlist);
	if (!word)
	{
		if (async)
			exit(1);
		return (-1);
	}
	dispose_wordlist(command->value.simplecom->wordlist);
	command->value.simplecom->wordlist = word;
	temp = wordlist2strarray(command->value.simplecom->wordlist);
	if (!temp)
	{
		if (async)
			exit(1);
		return (-1);
	}
	dprintf(1, "===%d === ", getpid());
	dprintf(1, "stdin -> %d stdout -> %d :  ", pipe_fd[0], pipe_fd[1]);
	ft_putstrarry_fd(temp, ", ", 1);
	free(temp);
	shell->last_status = 0;
	if (async)
		exit(0);
	return (0);
}

int	execute_pipeline(t_minishell *shell, t_command *command, int pipe_fd[2])
{
	int	status;
	int	prev;
	int	fildes[2];

	prev = pipe_fd[0];
	while (command->type == CT_CONNCOM
		&& command->value.conncom->type == CCT_PIPE)
	{
		if (pipe(fildes))
			return (-1);
		status = execute_command_internal(
			shell, command->value.conncom->command1, (int []){prev, fildes[1]});
		close(prev);
		close(fildes[1]);
		if (status < 0)
			return (-1);
		prev = fildes[0];
		command = command->value.conncom->command2;
	}
	status = execute_command_internal(shell, command, (int []){prev,
			pipe_fd[1]});
	close(prev);
	if (status < 0)
		return (-1);
	return (wait_for(shell, shell->last_pid));
}
