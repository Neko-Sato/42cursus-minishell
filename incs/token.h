/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 08:04:42 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/20 01:49:30 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_tokentype
{
	TK_WORD,
	TK_EOL,
	TK_INPUT,
	TK_HEREDOC,
	TK_OVEREWRITE,
	TK_APPEND,
	TK_PIPE,
	TK_AND,
	TK_OR,
	TK_OPEN_PAREN,
	TK_CLOSE_PAREN,
}				t_tokentype;

typedef struct s_token
{
	t_tokentype	type;
	char		*value;
}				t_token;

t_tokentype		match_token(char *str);
int				is_redirect_token(t_tokentype tokentype);

#endif
