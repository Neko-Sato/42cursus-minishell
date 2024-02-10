/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 02:55:01 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/10 12:49:39 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "command.h"
# include "lexer.h"

typedef struct s_parser
{
	t_lexical	*lexical;
	t_wordlist	**heredoc_tags;
	int			brackets_level;
}				t_parser;

int				parser(t_lexical *lexical, t_command **result,
					t_wordlist **heredoc_tags);

#endif