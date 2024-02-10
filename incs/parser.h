/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 02:55:01 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/11 00:43:19 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "command.h"
# include "lexer.h"

typedef struct s_parser
{
	t_lexical	*lexical;
	t_heredoc	**heredoc;
	int			brackets_level;
}				t_parser;

int				take_element(t_parser *parser, t_wordlist **wordlist,
					t_redirect **redirect);
int				take_command(t_parser *parser, t_command **command);
int				parser(t_lexical *lexical, t_command **command,
					t_heredoc **heredoc);
void			dispose_heredoc(t_heredoc *heredoc);

#endif