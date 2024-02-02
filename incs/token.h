/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 03:12:06 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/02 17:56:01 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stddef.h>

typedef enum e_token
{
	tk_none,
	tk_redirect_input,
	tk_here_doc,
	tk_redirect_append,
	tk_redirect_overwrite,
	tk_pipe,
	tk_or,
	tk_and,
}		t_token;

t_token	str2token(char *str);
int		is_redirect_token(t_token token);
int		is_connection_token(t_token token);

#endif
