/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:48:25 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/20 03:34:26 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "shell.h"
#include <libft.h>

static int	read_heredoc(t_minishell *shell, t_heredoc *heredoc);

int	gather_heredoc(t_minishell *shell)
{
	int			ret;
	t_heredoc	*heredoc;

	heredoc = shell->heredoc;
	while (heredoc)
	{
		ret = read_heredoc(shell, heredoc);
		if (ret)
			return (ret);
		heredoc = heredoc->next;
	}
	return (NOERR);
}

static int	read_heredoc(t_minishell *shell, t_heredoc *heredoc)
{
	int ret;
	size_t start;
	size_t zindex;

	start = shell->sindex;
	zindex = start;
	while (1)
	{
		ret = put_prompt(shell, PS2);
		if (ret)
			return (ret);
		if (!ft_strcmp(&shell->string[zindex], heredoc->eof))
			break ;
		zindex += ft_strlen(&shell->string[zindex]);
	}
	heredoc->contents = ft_substr(&shell->string[start], 0, zindex - start);
	if (!heredoc->contents)
		return (SYSTEM_ERR);
	shell->sindex = zindex;
	return (NOERR);
}