/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 23:17:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/20 03:22:55 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>
#include <readline.h>
#include <signal.h>
#include <stdlib.h>

static char	*strjoin_at_newline(char *line, char *new_line);
static void	signal_handler(int signal);
int			g_interrupt_state = 0;

char	*minishell_readline(t_minishell *shell, char *prompt)
{
	char	*line;

	if (shell->isinteractive)
	{
		g_interrupt_state = 0;
		rl_event_hook = (void *)ft_noop;
		signal(SIGINT, signal_handler);
		line = readline(prompt);
		signal(SIGINT, NULL);
	}
	else
		line = readline(NULL);
	if (g_interrupt_state)
	{
		free(line);
		line = NULL;
	}
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

int	put_prompt(t_minishell *shell, char *prompt)
{
	char	*line;
	char	*temp;

	line = minishell_readline(shell, prompt);
	if (g_interrupt_state)
		return (INTERRUPT);
	if (!line)
		return (NOERR);
	shell->line++;
	if (shell->string)
	{
		temp = strjoin_at_newline(shell->string, line);
		free(line);
		if (!temp)
			return (SYSTEM_ERR);
	}
	else
		temp = line;
	free(shell->string);
	shell->string = temp;
	return (NOERR);
}

static char	*strjoin_at_newline(char *line, char *new_line)
{
	char	*ret;
	size_t	size;

	size = ft_strlen(line) + ft_strlen(new_line) + 2;
	ret = (char *)malloc(sizeof(char) * size);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, line, size);
	ft_strlcat(ret, "\n", size);
	ft_strlcat(ret, new_line, size);
	return (ret);
}
