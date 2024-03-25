/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 23:17:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/25 17:59:43 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>

static char	*strjoin_at_newline(char *line, char *new_line);

char	*minishell_readline(t_minishell *shell)
{
	char	*prompt;
	char	*line;

	g_interrupt_state = 0;
	prompt = NULL;
	if (shell->isinteractive)
	{
		if (!shell->string)
			prompt = PS1;
		else
			prompt = PS2;
	}
	line = readline(prompt);
	if (g_interrupt_state)
	{
		free(line);
		shell->last_status = 128 | SIGINT;
	}
	return (line);
}

int	put_prompt(t_minishell *shell)
{
	char	*line;
	char	*temp;

	line = minishell_readline(shell);
	if (g_interrupt_state)
		return (INTERRUPT);
	if (!line)
		return (NOERR);
	if (shell->string)
	{
		temp = strjoin_at_newline(shell->string, line);
		free(line);
		if (!temp)
			return (FATAL_ERR);
		shell->line++;
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

	if (!line)
		line = "";
	if (!new_line)
		new_line = "";
	size = ft_strlen(line) + ft_strlen(new_line) + 2;
	ret = (char *)malloc(sizeof(char) * size);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, line, size);
	ft_strlcat(ret, "\n", size);
	ft_strlcat(ret, new_line, size);
	return (ret);
}
