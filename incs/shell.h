/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:49:22 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/12 18:25:33 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "command.h"
# include "jobs.h"
# include "token.h"
# include <stddef.h>
# include <sys/types.h>

# define PS1 "minishell> "
# define PS2 "> "

# define NOERR 0
# define SYSTEM_ERR -1
# define SYNTAX_ERR 1
# define INTERRUPT 2

typedef struct s_minishell
{
	pid_t		pid;
	char		*string;
	size_t		sindex;
	size_t		line;
	t_token		token;
	int			brackets_level;
	t_command	*command;
	t_heredoc	*heredoc;
	t_proc		*pidlist;
	char		**envp;
	int			last_status;
	int			isinteractive;
	int			eof_reached;
}				t_minishell;

extern int		g_interrupt_state;

int				shell_init(t_minishell *shell, char *envp[]);
void			shell_deinit(t_minishell *shell);
int				reader_loop(t_minishell *shell);

char			*minishell_readline(t_minishell *shell);
int				put_prompt(t_minishell *shell);

#endif