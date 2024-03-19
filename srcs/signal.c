/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:49:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 17:58:14 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline.h>
#include <signal.h>

int			g_interrupt_state = 0;

static void	signal_handler(int signal);

int	set_signal(void)
{
	struct sigaction	act;

	act.sa_handler = signal_handler;
	act.sa_flags = SA_RESTART;
	if (sigemptyset(&act.sa_mask))
		return (-1);
	if (sigaction(SIGINT, &act, NULL))
		return (-1);
	act.sa_handler = SIG_IGN;
	act.sa_flags = 0;
	if (sigemptyset(&act.sa_mask))
		return (-1);
	if (sigaction(SIGQUIT, &act, NULL))
		return (-1);
	return (0);
}

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_interrupt_state = 1;
		rl_done = 1;
	}
}
