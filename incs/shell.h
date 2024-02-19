/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:49:22 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/20 01:42:02 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "command.h"
# include <stddef.h>

# define PS1 "minishell> "
# define PS2 "> "

typedef struct s_minishell
{
	char		*string;
	size_t		sindex;
	size_t		line;
	t_command	*command;
	t_heredoc	*heredoc;
	char		**envp;
	int			last_status;
	int			isinteractive;
}				t_minishell;

extern int		g_interrupt_state;

char			*minishell_readline(t_minishell *shell, char *prompt);
int				put_prompt(t_minishell *shell, char *prompt);

#endif