/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:56:31 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/07 02:26:15 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "token.h"
# include <stddef.h>

typedef struct s_lexical
{
	struct s_lexical	*next;
	t_token				token;
	char				*value;
}						t_lexical;

typedef struct s_lexer
{
	char				*line;
	size_t				pos;
	t_lexical			**next_lexical;
}						t_lexer;

int						lexer(char *line, t_lexical **result);
void					lexical_dispose(t_lexical *lexical);

int						skip_space(t_lexer *lexer);
int						skip_word(t_lexer *lexer);

#endif