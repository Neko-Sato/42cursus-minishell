/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_disk_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:29:01 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 07:36:45 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "shell.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	execute_disk_command_internal(
				t_minishell *shell, t_execute_simple *vars);
static int	init_execve_args(t_minishell *shell,
				t_execute_simple *vars, t_execve_args *args);

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

static int	execute_disk_command_internal(
	t_minishell *shell, t_execute_simple *vars)
{
	int				ret;
	t_execve_args	args;

	while (1)
	{
		ret = init_execve_args(shell, vars, &args);
		if (!ret)
			ret = do_piping(shell, vars->vars->pipe_in, vars->vars->pipe_out);
		if (!ret)
			ret = do_redirect(shell, vars->redirect);
		if (ret)
			return (ret);
		close_fds(vars->vars->fds_to_close_size, vars->vars->fds_to_close);
		ret = execve(args.pathname, args.argv, args.envp);
		break ;
	}
	free(args.pathname);
	free(args.argv);
	if (ret != -1)
		exit(ret);
	return (ret);
}

static int	init_execve_args(t_minishell *shell,
				t_execute_simple *vars, t_execve_args *args)
{
	args->argv = wordlist2strarray(vars->wordlist);
	if (!args->argv)
		return (-1);
	if (!ft_strchr(args->argv[0], '/'))
	{
		if (search_for_command(shell, args->argv[0], &args->pathname))
			return (-1);
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
		return (-1);
	args->envp = shell->envp;
	return (0);
}
