/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_disk_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:29:01 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 02:16:27 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "shell.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	execute_disk_command_internal(t_minishell *shell,
				t_execute_simple *vars);

int	execute_disk_command(t_minishell *shell, t_execute_simple vars)
{
	int		status;
	pid_t	pid;

	pid = -1;
	if (!vars.already_fork)
	{
		pid = make_child(shell);
		if (pid == -1)
			return (-1);
		else if (pid)
			return (wait_for(shell, pid));
	}
	status = execute_disk_command_internal(shell, &vars);
	if (status == -1)
		perror("minishell");
	exit(EXIT_FAILURE);
}

//もtttっときれいに書きなさい
static int	execute_disk_command_internal(t_minishell *shell,
				t_execute_simple *vars)
{
	char *pathname;
	char **argv;
	char **envp;

	argv = wordlist2strarray(vars->wordlist);
	if (!argv)
		return (-1);
	pathname = argv[0];
	if (!ft_strchr(pathname, '/'))
	{
		if (search_for_command(shell, pathname, &pathname))
			return (-1);
		if (!pathname)
		{
			ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
			ft_putendl_fd(argv[0], STDERR_FILENO);
			free(argv);
			exit(127);
		}
	}
	envp = shell->envp;
	if (do_piping(shell, vars->vars->pipe_in, vars->vars->pipe_out))
		return (-1);
	if (do_redirect(shell, vars->redirect))
		return (-1);
	close_fds(vars->vars->fds_to_close_size, vars->vars->fds_to_close);
	execve(pathname, argv, envp);
	if (!ft_strchr(argv[0], '/'))
		free(pathname);
	free(argv);
	return (-1);
}
