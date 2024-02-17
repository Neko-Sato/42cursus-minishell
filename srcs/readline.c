/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 23:17:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/17 19:15:51 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>
#include <stdio.h>
#include <readline.h>
#include <signal.h>
#include <stdlib.h>

static void	signal_handler(int signal);
int			g_interrupt_state = 0;

char	*minishell_readline(char *prompt, int interactive)
{
	char	*line;

	if (interactive)
	{
		g_interrupt_state = 0;
		rl_event_hook = (void *)ft_noop;
		signal(SIGINT, signal_handler);
		line = readline(prompt);
		signal(SIGINT, NULL);
	}
	else
		line = readline(NULL);
	return (line);
}

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_done = 1;
		g_interrupt_state = 1;
	}
}