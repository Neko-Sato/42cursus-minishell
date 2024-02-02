/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:26:29 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/02 14:31:51 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <libft.h>

t_token	str2token(char *str)
{
	if (!ft_strncmp("<<", str, 2))
		return (tk_here_doc);
	else if (!ft_strncmp("<", str, 1))
		return (tk_redirect_input);
	else if (!ft_strncmp(">", str, 1))
		return (tk_redirect_overwrite);
	else if (!ft_strncmp(">>", str, 2))
		return (tk_redirect_append);
	else if (!ft_strncmp("|", str, 1))
		return (tk_pipe);
	else if (!ft_strncmp("||", str, 2))
		return (tk_or);
	else if (!ft_strncmp("&&", str, 2))
		return (tk_and);
	return (tk_none);
}
