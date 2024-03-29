/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 02:55:01 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/30 02:39:16 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "command.h"
# include "lexer.h"

int	parser(t_minishell *shell);
int	gather_heredoc(t_minishell *shell);

int	take_command(t_minishell *shell);
int	take_basiccom(t_minishell *shell);
int	take_blockcom(t_minishell *shell);
int	take_groupcom(t_minishell *shell);
int	take_simplecom(t_minishell *shell);
int	take_concom(t_minishell *shell);

int	take_element(t_minishell *shell, t_element *element);

#endif