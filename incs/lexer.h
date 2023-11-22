/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:59:33 by hshimizu          #+#    #+#             */
/*   Updated: 2023/11/22 14:38:26 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token
{
	TOKEN_WORD,
	TOKEN_EOL,
	TOKEN_REDIRECT_IN,
	TOKEN_HERE_DOC,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_OUT_APPEND,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_VAR,
	TOKEN_LAST_EXIT_STATUS,
}			t_token;

typedef struct s_lex
{
	t_token	type;
}			t_lex;

typedef struct s_lex_word
{
	t_token	type;
	char	*str;
}			t_lex_str;

t_lex		**lexer(char *str);

#endif