/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:49:22 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/11 03:24:44 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"

# define PS1 "minishell> "
# define PS2 "> "

extern int	g_interrupt_state;

char		*put_primary_prompt(t_minishell *gvars);
char		*put_secondary_prompt(t_minishell *gvars, char *line);

#endif