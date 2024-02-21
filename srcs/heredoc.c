/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:48:25 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/22 00:34:04 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "shell.h"
#include <libft.h>
#include <stdio.h>

static int	read_heredoc(t_minishell *shell, t_heredoc *heredoc);
static int	read_contents(t_minishell *shell, t_heredoc *heredoc,
				size_t *zindex);
static int	check_eof(t_minishell *shell, t_heredoc *heredoc, size_t *zindex,
				size_t pram[3]);
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
	size_t	zindex;

	zindex = shell->sindex;
	ret = read_contents(shell, heredoc, &zindex);
	if (ret)
		return (ret);
	shell->sindex = zindex;
	return (NOERR);
}

// parm
// 0: eof_len
// 1: start
// 2: len
static int	read_contents(t_minishell *shell, t_heredoc *heredoc,
		size_t *zindex)
{
	int		ret;
	size_t	pram[3];

	pram[0] = ft_strlen(heredoc->eof);
	ret = NOERR;
	pram[1] = *zindex;
	while (1)
	{
		if (!shell->string[*zindex])
			ret = put_prompt(shell);
		if (ret)
			return (ret);
		if (check_eof(shell, heredoc, zindex, pram))
			break ;
		while (!ft_strchr("\n", shell->string[*zindex]))
			(*zindex)++;
	}
	heredoc->contents = ft_substr(&shell->string[pram[1]], 1, pram[2]);
	return (NOERR);
}

static int	check_eof(t_minishell *shell, t_heredoc *heredoc, size_t *zindex,
		size_t pram[3])
{
	if (!shell->string[*zindex])
	{
		put_warning(heredoc);
		pram[2] = *zindex - pram[1];
		return (1);
	}
	(*zindex)++;
	if (!ft_strncmp(&shell->string[*zindex], heredoc->eof, pram[0])
		&& ft_strchr("\n", shell->string[*zindex + pram[0]]))
	{
		pram[2] = *zindex - pram[1];
		*zindex += pram[0];
		return (1);
	}
	return (0);
}

static void	put_warning(t_heredoc *heredoc)
{
	ft_putstr_fd("minishell: warning: Finished reading the heredoc `",
		STDERR_FILENO);
	ft_putstr_fd(heredoc->eof, STDERR_FILENO);
	ft_putstr_fd("`\n", STDERR_FILENO);
}
