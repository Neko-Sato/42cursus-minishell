/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 08:03:52 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/20 08:32:43 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <libft.h>

t_tokentype	match_token(char *str)
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
	if (ft_strchr("\n", *str))
		return (TK_EOL);
	return (TK_WORD);
}

int	is_redirect_token(t_tokentype tokentype)
{
	return (TK_INPUT <= tokentype && tokentype <= TK_APPEND);
}
