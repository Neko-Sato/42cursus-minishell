/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:26:29 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/02 17:55:51 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <libft.h>

t_token	str2token(char *str)
{
	if (!ft_strncmp("<<", str, 2))
		return (tk_here_doc);
	if (!ft_strncmp("<", str, 1))
		return (tk_redirect_input);
	if (!ft_strncmp(">", str, 1))
		return (tk_redirect_overwrite);
	if (!ft_strncmp(">>", str, 2))
		return (tk_redirect_append);
	if (!ft_strncmp("|", str, 1))
		return (tk_pipe);
	if (!ft_strncmp("||", str, 2))
		return (tk_or);
	if (!ft_strncmp("&&", str, 2))
		return (tk_and);
	return (tk_none);
}

size_t	get_token_len(t_token token)
{
	return (((int[]){0, 1, 2, 1, 2, 1, 2, 2})[token]);
}

int	is_redirect_token(t_token token)
{
	return (token == tk_redirect_input || token == tk_here_doc
		|| token == tk_redirect_overwrite || token == tk_redirect_append);
}

int	is_connection_token(t_token token)
{
	return (token == tk_pipe || token == tk_and || token == tk_or);
}