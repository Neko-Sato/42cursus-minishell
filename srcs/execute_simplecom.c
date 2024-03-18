/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simplecom.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:13:45 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 08:29:49 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "execute.h"
#include "shell.h"
#include "subst.h"
#include <stdio.h>
#include <stdlib.h>

static int	execute_simplecom_internal(t_minishell *shell,
				t_simplecom *simplecom, t_execute *vars, int already_fork);

int	execute_simplecom(t_minishell *shell, t_simplecom *simplecom,
		t_execute vars)
{
	pid_t	pid;
	int		do_fork;
	int		status;

	do_fork = vars.pipe_in != -1 || vars.pipe_out != -1;
	if (do_fork)
	{
		pid = make_child(shell);
		if (pid == -1)
			return (-1);
		else if (pid)
		{
			if (vars.pipe_out == -1)
				return (wait_for(shell, pid));
			return (EXIT_SUCCESS);
		}
	}
	status = execute_simplecom_internal(shell, simplecom, &vars, do_fork);
	if (!do_fork)
		return (status);
	if (status == -1)
		perror("minishell");
	exit(EXIT_FAILURE);
}

static int	execute_simplecom_internal(t_minishell *shell,
		t_simplecom *simplecom, t_execute *vars, int already_fork)
{
	int			status;
	t_wordlist	*wordlist;

	if (!simplecom->wordlist)
		return (execute_null_command(shell, (t_execute_simple){NULL,
				simplecom->redirect, vars, already_fork}));
	wordlist = expand_wordlist(shell, simplecom->wordlist);
	if (!wordlist)
		return (-1);
	if (isbuiltin(wordlist->word))
		status = execute_builtin(shell, (t_execute_simple){
				wordlist, simplecom->redirect, vars, already_fork});
	else
		status = execute_disk_command(shell, (t_execute_simple){
				wordlist, simplecom->redirect, vars, already_fork});
	dispose_wordlist(wordlist);
	return (status);
}
