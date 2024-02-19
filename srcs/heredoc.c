/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:48:25 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/20 04:58:21 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "shell.h"
#include <libft.h>
#include <stdio.h>

static int	read_heredoc(t_minishell *shell, t_heredoc *heredoc);
static int	skip_eof(t_minishell *shell, t_heredoc *heredoc, size_t *zindex);
static void	put_warning(t_heredoc *heredoc);

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
	int		ret;
	size_t	start;
	size_t	zindex;

	zindex = shell->sindex;
	zindex++;
	start = zindex;
	ret = skip_eof(shell, heredoc, &zindex);
	if (ret)
		return (ret);
	heredoc->contents = ft_substr(&shell->string[start], 0, zindex - start);
	if (!heredoc->contents)
		return (SYSTEM_ERR);
	//	変数展開
	shell->sindex = zindex;
	return (NOERR);
}

static int	skip_eof(t_minishell *shell, t_heredoc *heredoc, size_t *zindex)
{
	int	ret;

	while (1)
	{
		ret = put_prompt(shell, heredoc->eof);
		if (ret)
			return (ret);
		if (!ft_strcmp(&shell->string[*zindex], heredoc->eof))
			break ;
		if (!shell->string[*zindex])
		{
			put_warning(heredoc);
			break ;
		}
		*zindex += ft_strlen(&shell->string[*zindex]) + 1;
	}
	return (NOERR);
}

static void	put_warning(t_heredoc *heredoc)
{
	ft_putstr_fd("minishell: warning: Finished reading the heredoc `",
		STDERR_FILENO);
	ft_putstr_fd(heredoc->eof, STDERR_FILENO);
	ft_putstr_fd("`\n", STDERR_FILENO);
}
