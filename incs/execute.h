/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:43:27 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/12 18:57:19 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "command.h"
# include "shell.h"

int	execute_command(t_minishell *shell, t_command *command);

int	execute_command_internal(t_minishell *shell, t_command *command,
		int pipe_fd[2]);
int	execute_simplecom(t_minishell *shell, t_command *command, int pipe_fd[2]);
int	execute_groupcom(t_minishell *shell, t_command *command, int pipe_fd[2]);
int	execute_conncom(t_minishell *shell, t_command *command, int pipe_fd[2]);
int	execute_pipeline(t_minishell *shell, t_command *command, int pipe_fd[2]);

#endif
