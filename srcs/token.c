/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 08:03:52 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/09 09:06:18 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <libft.h>

t_token	match_token(char *str)
{
	if (!ft_strncmp("<<", str, 2))
		return (TK_HEREDOC);
	if (!ft_strncmp("<", str, 1))
		return (TK_INPUT);
	if (!ft_strncmp(">>", str, 2))
		return (TK_APPEND);
	if (!ft_strncmp(">", str, 1))
		return (TK_OVEREWRITE);
	if (!ft_strncmp("||", str, 2))
		return (TK_OR);
	if (!ft_strncmp("|", str, 1))
		return (TK_PIPE);
	if (!ft_strncmp("&&", str, 2))
		return (TK_AND);
	if (!ft_strncmp("(", str, 1))
		return (TK_OPEN_PAREN);
	if (!ft_strncmp(")", str, 1))
		return (TK_CLOSE_PAREN);
	return (TK_NONE);
}

int	is_redirect_token(t_token token)
{
	return (2 <= token && token <= 5);
}

int	is_connection_token(t_token token)
{
	return (6 <= token && token <= 8);
}
