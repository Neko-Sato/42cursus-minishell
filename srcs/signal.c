/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:49:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/28 22:24:09 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>
#include <stdio.h>
#include <readline.h>
#include <signal.h>
#include <unistd.h>

int			g_interrupt_state = 0;

static void	signal_handler(int signal);

int	set_signal(void)
{
	struct sigaction	act;

	act.sa_handler = signal_handler;
	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGINT, &act, NULL))
	{
		perror("minishell: sigaction");
		return (SYSTEM_ERR);
	}
	signal(SIGQUIT, SIG_IGN);
	return (NOERR);
}

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_interrupt_state = 1;
		rl_done = 1;
	}
}
