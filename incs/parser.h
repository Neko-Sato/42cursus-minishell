/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 02:55:01 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/20 02:06:56 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "command.h"
# include "lexer.h"

typedef struct s_parser
{
	t_token		token;
	int			brackets_level;
	t_command	*command;
	t_heredoc	*heredoc;
	t_heredoc	**heredoc_last;
}				t_parser;

int				parser(t_minishell *shell);
int				gather_heredoc(t_minishell *shell);

int				take_command(t_minishell *shell, t_parser *parser);
int				take_blockcom(t_minishell *shell, t_parser *parser);
int				take_simplecom(t_minishell *shell, t_parser *parser);
int				take_groupcom(t_minishell *shell, t_parser *parser);
int				take_concom(t_minishell *shell, t_parser *parser);

int				take_element(t_minishell *shell, t_parser *parser,
					t_element *element);

#endif