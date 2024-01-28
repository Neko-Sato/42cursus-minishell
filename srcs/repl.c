/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 09:19:31 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/28 20:55:04 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "minishell.h"
#include "repl.h"
#include <libft.h>
#include <readline.h>
#include <signal.h>

static void	sigint_handler(int n);
static int	event_hook_noop(void);

int			interruption = 0;

int	reader_loop(t_minishell *gvars)
{
	if (gvars->isinteractive)
		signal(SIGINT, sigint_handler);
	while (1)
	{
	}
	if (gvars->isinteractive)
		ft_putendl_fd("exit", 2);
	return (0);
}

static void	sigint_handler(int n)
{
	interruption = 1;
	rl_done = 1;
}
