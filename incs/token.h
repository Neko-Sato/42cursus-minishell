/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 08:04:42 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/10 09:56:37 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token
{
	TK_NONE,
	TK_WORD,
	TK_INPUT,
	TK_HEREDOC,
	TK_OVEREWRITE,
	TK_APPEND,
	TK_PIPE,
	TK_AND,
	TK_OR,
	TK_OPEN_PAREN,
	TK_CLOSE_PAREN,
}		t_token;

t_token	match_token(char *str);
int		is_redirect_token(t_token token);
int		is_connection_token(t_token token);

#endif
