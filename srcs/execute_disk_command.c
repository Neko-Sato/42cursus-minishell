/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_disk_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:29:01 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 19:37:45 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "shell.h"
#include <errno.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

static int	execute_disk_command_internal(t_minishell *shell,
				t_execute_simple *vars);
static int	init_execve_args(t_minishell *shell,
				t_execute_simple *vars, t_execve_args *args);
static int	do_err(char *pathname);

int	execute_disk_command(t_minishell *shell, t_execute_simple vars)
{
	int		status;
	pid_t	pid;

	pid = -1;
	if (!vars.already_fork)
	{
		pid = make_child(shell);
		if (pid < 0)
			return (pid);
		else if (pid)
			return (wait_for(shell, pid));
	}
	status = execute_disk_command_internal(shell, &vars);
	if (status == FATAL_ERR)
		perror("minishell");
	exit(EXIT_FAILURE);
}

static int	execute_disk_command_internal(
	t_minishell *shell, t_execute_simple *vars)
{
	int				ret;
	t_execve_args	args;

	ret = init_execve_args(shell, vars, &args);
	if (!ret)
		ret = do_piping(shell, vars->vars->pipe_in, vars->vars->pipe_out);
	if (!ret)
		ret = do_redirect(shell, vars->redirect);
	close_fds(vars->vars->fds_to_close_size, vars->vars->fds_to_close);
	if (!ret && execve(args.pathname, args.argv, args.envp))
		ret = do_err(args.pathname);
	free(args.pathname);
	free(args.argv);
	ft_2darraydel(args.envp);
	if (0 <= ret)
		exit(ret);
	return (ret);
}

static int	init_execve_args(t_minishell *shell,
	t_execute_simple *vars, t_execve_args *args)
{
	ft_bzero(args, sizeof(t_execve_args));
	args->argv = wordlist2strarray(vars->wordlist);
	if (!args->argv)
		return (FATAL_ERR);
	if (!ft_strchr(args->argv[0], '/'))
	{
		if (search_for_command(shell, args->argv[0], &args->pathname))
			return (FATAL_ERR);
		if (!args->pathname)
		{
			ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
			ft_putendl_fd(args->argv[0], STDERR_FILENO);
			return (127);
		}
	}
	else
		args->pathname = ft_strdup(args->argv[0]);
	if (!args->pathname)
		return (FATAL_ERR);
	args->envp = get_envp(shell);
	if (!args->envp)
		return (FATAL_ERR);
	return (NOERR);
}

static int	do_err(char *pathname)
{
	int	status;

	if (errno == ENOEXEC)
	{
		perror("minishell: execve");
		return (SYSTEM_ERR);
	}
	status = (int []){127, 126}[!(errno == ENOENT)];
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(pathname, STDERR_FILENO);
	return (status);
}
