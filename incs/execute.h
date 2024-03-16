/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:43:27 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/16 12:06:09 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "command.h"
# include "shell.h"

typedef struct s_execute
{
	t_wordlist	*wordlist;
	t_redirect	*redirect;
	int			pipe_in;
	int			pipe_out;
	int			already_fork;
}				t_execute;

typedef struct s_execute_simplecom
{
	t_simplecom	*simplecom;
	int			pipe_in;
	int			pipe_out;
	int			already_fork;
}				t_execute_simplecom;

int				execute_command(t_minishell *shell, t_command *command);

int				execute_command_internal(t_minishell *shell, t_command *command,
					int pipe_in, int pipe_out);
int				execute_simplecom(t_minishell *shell, t_simplecom *command,
					int pipe_in, int pipe_out);
int				execute_pipeline(t_minishell *shell, t_command *command,
					int pipe_in, int pipe_out);

int				execute_null_command(t_minishell *shell, t_execute vars);
int				execute_builtin(t_minishell *shell, t_execute vars);
int				execute_disk_command(t_minishell *shell, t_execute vars);

int				search_for_command(t_minishell *shell, char *pathname,
					char **result);

int				save_stdio(t_minishell *shell);
int				adapt_stdio(t_minishell *shell);
int				do_piping(t_minishell *shell, int pipe_in, int pipe_out);
int				do_redirect_in(t_minishell *shell, t_redirect *redirect);
int				do_redirect_out(t_minishell *shell, t_redirect *redirect);
int				do_redirect(t_minishell *shell, t_redirect *redirect);

#endif
