/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 09:19:31 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/28 21:16:25 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "minishell.h"
#include "repl.h"
#include <libft.h>
#include <readline.h>
#include <signal.h>

static void	sigint_handler(int n);

int			interruption = 0;

int	reader_loop(t_minishell *gvars)
{
	t_repl	repl;

	if (gvars->isinteractive)
		signal(SIGINT, sigint_handler);
	while (1)
	{
		while (1)
		{
			// if (reader_command())
			// 	return (-1);
			// if (interruption)
			// 	break ;
			// if (reader_heredoc())
			// 	return (-1);
			// if (interruption)
			// 	break ;
			// execute_command();
			break ;
		}
		// dispose_command();
		// dispose_heredoc();
	}
	if (gvars->isinteractive)
		ft_putendl_fd("exit", STDERR_FILENO);
	return (repl.status_code);
}

static void	sigint_handler(int n)
{
	interruption = 1;
	rl_done = 1;
}
