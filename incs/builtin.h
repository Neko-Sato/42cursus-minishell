/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:08:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 08:32:34 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "command.h"
# include "shell.h"

int	builtin_echo(int argc, char *argv[]);
int	builtin_env(int argc, char *argv[], char *envp[]);
int	builtin_cd(t_minishell *shell, t_wordlist *list);
int	builtin_pwd(t_minishell *shell, t_wordlist *list);
int	builtin_export(t_minishell *shell, t_wordlist *list);
int	builtin_exit(t_minishell *shell, t_wordlist *list);

#endif