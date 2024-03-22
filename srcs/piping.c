/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:44:47 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/22 18:13:10 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <unistd.h>

int	do_piping(t_minishell *shell, int pipe_in, int pipe_out)
{
	int	ret;

	(void)shell;
	ret = 0;
	if (!ret && pipe_in != -1)
	{
		ret = -(dup2(pipe_in, STDIN_FILENO) == -1);
		close(pipe_in);
	}
	if (!ret && pipe_out != -1)
	{
		ret = -(dup2(pipe_out, STDOUT_FILENO) == -1);
		close(pipe_out);
	}
	return (ret);
}

int	save_stdio(t_minishell *shell)
{
	shell->save_stdio[0] = dup(STDIN_FILENO);
	if (shell->save_stdio[0] == -1)
		return (-1);
	shell->save_stdio[1] = dup(STDOUT_FILENO);
	if (shell->save_stdio[1] == -1)
		return (-1);
	return (0);
}

int	restore_stdio(t_minishell *shell)
{
	if (shell->save_stdio[0] != -1)
	{
		if (dup2(shell->save_stdio[0], STDIN_FILENO) == -1)
			return (-1);
		close(shell->save_stdio[0]);
		shell->save_stdio[0] = -1;
	}
	if (shell->save_stdio[1] != -1)
	{
		if (dup2(shell->save_stdio[1], STDOUT_FILENO) == -1)
			return (-1);
		close(shell->save_stdio[1]);
		shell->save_stdio[1] = -1;
	}
	return (0);
}

void	close_fds(size_t size, int *fds)
{
	size_t	i;

	i = 0;
	while (i < size)
		close(fds[i++]);
}
