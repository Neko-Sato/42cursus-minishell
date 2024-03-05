/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:48:25 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/06 01:41:03 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "shell.h"
#include "subst.h"
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

/*
! 必須　：eofはクォートを外して解釈する
heredocのリストからdocumentを持ってきて
eofにクォートがあればフラグを建てて
eofをunquoteしたものに上書きする
documentを読んで代入して
heredocリストから消す

*/

static int	read_heredoc(t_minishell *shell, t_document *document,
				size_t *zindex);
static int	read_document(t_minishell *shell, t_document *document,
				size_t *zindex);
static int	check_eof(t_minishell *shell, t_document *document, size_t *zindex,
				size_t var[3]);
static void	put_warning(char *eof);

int	gather_heredoc(t_minishell *shell)
{
	int			ret;
	size_t		zindex;
	t_heredoc	*temp;

	while (shell->heredoc)
	{
		zindex = shell->sindex;
		temp = shell->heredoc;
		ret = read_heredoc(shell, temp->document, &zindex);
		if (ret)
			return (ret);
		shell->heredoc = temp->next;
		free(temp);
		shell->sindex = zindex;
	}
	return (NOERR);
}

static int	read_heredoc(t_minishell *shell, t_document *document,
		size_t *zindex)
{
	char	*temp;

	document->quoted = ft_strchr(document->eof, '\'')
		|| ft_strchr(document->eof, '"');
	if (document->quoted)
	{
		temp = string_quote_removal(document->eof);
		if (!temp)
			return (SYSTEM_ERR);
		free(document->eof);
		document->eof = temp;
	}
	return (read_document(shell, document, zindex));
}

#define RD_LEN 0
#define RD_START 1
#define RD_EOF_LEN 2

static int	read_document(t_minishell *shell, t_document *document,
		size_t *zindex)
{
	size_t	var[3];
	int		ret;

	ret = 0;
	var[RD_EOF_LEN] = ft_strlen(document->eof);
	var[RD_START] = *zindex;
	while (1)
	{
		if (!shell->string[*zindex])
			ret = put_prompt(shell);
		if (ret)
			return (ret);
		if (check_eof(shell, document, zindex, var))
			break ;
	}
	document->document = ft_substr(&shell->string[var[RD_START]], 1,
			var[RD_LEN]);
	if (!document->document)
		return (SYSTEM_ERR);
	return (NOERR);
}

static int	check_eof(t_minishell *shell, t_document *document, size_t *zindex,
		size_t var[3])
{
	if (!shell->string[*zindex])
	{
		put_warning(document->eof);
		var[RD_LEN] = *zindex - var[RD_START];
		return (1);
	}
	(*zindex)++;
	if (!ft_strncmp(&shell->string[*zindex], document->eof, var[RD_EOF_LEN])
		&& ft_strchr("\n", shell->string[*zindex + var[RD_EOF_LEN]]))
	{
		var[RD_LEN] = *zindex - var[RD_START];
		*zindex += var[RD_EOF_LEN];
		return (1);
	}
	while (!ft_strchr("\n", shell->string[*zindex]))
		(*zindex)++;
	return (0);
}

static void	put_warning(char *eof)
{
	ft_putstr_fd("minishell: warning: Finished reading the heredoc `",
		STDERR_FILENO);
	ft_putstr_fd(eof, STDERR_FILENO);
	ft_putstr_fd("`\n", STDERR_FILENO);
}
