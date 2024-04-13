/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:49:22 by hshimizu          #+#    #+#             */
/*   Updated: 2024/04/12 05:29:47 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "command.h"
# include "jobs.h"
# include "token.h"
# include "variable.h"
# include <stddef.h>
# include <sys/types.h>

# define DEFAULT_PATH \
	"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

# define PS1 "\1\033[32m\2minishell> \1\033[0m\2"
# define PS2 "\1\033[32m\2> \033\1[0m\2"

# define NOERR 0
# define FATAL_ERR -1
# define SYSTEM_ERR -2
# define SYNTAX_ERR -3
# define INTERRUPT -4

typedef struct s_minishell
{
	char		*cwd;
	pid_t		pid;
	char		*string;
	size_t		sindex;
	size_t		line;
	t_token		token;
	int			brackets_level;
	t_command	*command;
	t_heredoc	*heredoc;
	t_proc		*pidlist;
	int			save_stdio[2];
	t_var		**vars;
	size_t		vars_len;
	int			last_status;
	int			isinteractive;
	int			eof_reached;
	int			exit_immediately;
}				t_minishell;

extern int		g_interrupt_state;

int				shell_init(t_minishell *shell, char *envp[]);
void			shell_deinit(t_minishell *shell);
int				init_variable(t_minishell *shell, char *envp[]);
int				reader_loop(t_minishell *shell);

char			*minishell_readline(t_minishell *shell);
int				put_prompt(t_minishell *shell);
int				set_signal(void);

#endif