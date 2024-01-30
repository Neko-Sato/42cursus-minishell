/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 03:12:06 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/31 03:18:38 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include <stddef.h>

int	skip_space(t_minishell *gvars, char **line, size_t *pos);
int	skip_backslash(t_minishell *gvars, char **line, size_t *pos);
int	skip_singlquote(t_minishell *gvars, char **line, size_t *pos);
int	skip_doublequote(t_minishell *gvars, char **line, size_t *pos);

#endif
