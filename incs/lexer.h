/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:56:31 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/19 23:39:04 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "shell.h"
# include "token.h"
# include <stddef.h>

int	lexer(t_minishell *shell, t_token *token);
int	skip_space(t_minishell *shell, size_t *zindex);
int	get_word(t_minishell *shell, size_t *zindex, char **word);
int	skip_singlquote(t_minishell *shell, size_t *zindex);
int	skip_doublequote(t_minishell *shell, size_t *zindex);

#endif