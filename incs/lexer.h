/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:59:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/18 20:17:04 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
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
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
}					t_token;

typedef struct s_token_word
{
	t_token_type	type;
	char			*str;
}					t_token_word;

typedef struct s_token_redirect
{
	t_token_type	type;
	int				fileno;
	char			*name;
}					t_token_word;

typedef char		*(*t_line_fn)(void);

t_token				**lexer(t_line_fn line_fn);

#endif