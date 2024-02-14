/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:49:22 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/14 18:20:37 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define PS1 "minishell> "
# define PS2 "> "

extern int	g_interrupt_state;

char		*minishell_readline(char *prompt, int interactive);

#endif