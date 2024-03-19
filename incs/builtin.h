/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:08:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 15:58:28 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "command.h"
# include "shell.h"

typedef int	(*t_builtin_fun)(t_minishell *shell, t_wordlist *wordlist);

int			builtin_echo(t_minishell *shell, t_wordlist *wordlist);
int			builtin_env(t_minishell *shell, t_wordlist *wordlist);
int			builtin_cd(t_minishell *shell, t_wordlist *wordlist);
int			builtin_pwd(t_minishell *shell, t_wordlist *wordlist);
int			builtin_export(t_minishell *shell, t_wordlist *wordlist);
int			builtin_exit(t_minishell *shell, t_wordlist *wordlist);

#endif