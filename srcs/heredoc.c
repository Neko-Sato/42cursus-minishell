/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:48:25 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/21 00:22:04 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "shell.h"
#include <libft.h>

typedef struct s_read_contents
{
	size_t	eof_len;
	size_t	start;
	size_t	len;
}			t_read_contents;

static int	read_heredoc(t_minishell *shell, t_heredoc *heredoc);
static int	read_contents(t_minishell *shell, t_heredoc *heredoc,
				size_t *zindex);
static int	check_eof(t_minishell *shell, t_heredoc *heredoc, size_t *zindex,
				t_read_contents *pram);
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
	zindex++;
	ret = read_contents(shell, heredoc, &zindex);
	if (ret)
		return (ret);
	shell->sindex = zindex;
	return (NOERR);
}

static int	read_contents(t_minishell *shell, t_heredoc *heredoc,
		size_t *zindex)
{
	int				ret;
	t_read_contents	pram;

	pram.eof_len = ft_strlen(heredoc->eof);
	ret = NOERR;
	pram.start = *zindex;
	while (1)
	{
		if (!shell->string[*zindex])
			ret = put_prompt(shell, PS2);
		if (ret)
			return (ret);
		if (check_eof(shell, heredoc, zindex, &pram))
			break ;
		while (!ft_strchr("\n", shell->string[*zindex]))
			(*zindex)++;
	}
	heredoc->contents = ft_substr(&shell->string[pram.start], 0, pram.len);
	return (NOERR);
}

static int	check_eof(t_minishell *shell, t_heredoc *heredoc, size_t *zindex,
		t_read_contents *pram)
{
	if (!shell->string[*zindex])
	{
		put_warning(heredoc);
		pram->len = *zindex - pram->start;
		return (1);
	}
	(*zindex)++;
	if (!ft_strncmp(&shell->string[*zindex], heredoc->eof, pram->eof_len)
		&& ft_strchr("\n", shell->string[*zindex + pram->eof_len]))
	{
		pram->len = *zindex - pram->start;
		*zindex += pram->eof_len;
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
