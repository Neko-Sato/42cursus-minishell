/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:20:56 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 21:09:17 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "execute.h"
#include "subst.h"
#include <errno.h>
#include <fcntl.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	do_redirect_internal(t_minishell *shell, t_redirect *redirect);
static int	do_redirect_file(t_minishell *shell, t_redirect *redirect);
static int	do_redirect_heredoc(t_minishell *shell, t_redirect *redirect);

int	do_redirect(t_minishell *shell, t_redirect *redirect)
{
	int	ret;

	ret = NOERR;
	while (!ret && redirect)
	{
		ret = do_redirect_internal(shell, redirect);
		redirect = redirect->next;
	}
	return (ret);
}

static int	do_redirect_internal(t_minishell *shell, t_redirect *redirect)
{
	int	fd;

	fd = -1;
	if (redirect->type == RT_INPUT || redirect->type == RT_OVERWRITE
		|| redirect->type == RT_APPEND)
		fd = do_redirect_file(shell, redirect);
	else if (redirect->type == RT_HEREDOC)
		fd = do_redirect_heredoc(shell, redirect);
	if (fd < 0)
		return (fd);
	if (redirect->type == RT_INPUT || redirect->type == RT_HEREDOC)
		fd = dup2(fd, STDIN_FILENO);
	else if (redirect->type == RT_OVERWRITE || redirect->type == RT_APPEND)
		fd = dup2(fd, STDOUT_FILENO);
	if (fd != -1)
		return (NOERR);
	perror("minishell: dup2");
	return (SYSTEM_ERR);
}

static int	do_redirect_file(t_minishell *shell, t_redirect *redirect)
{
	int			fd;
	t_wordlist	*word;

	if (shell_expand_word(shell, redirect->value.filename, &word))
		return (FATAL_ERR);
	if (!word || word->next)
	{
		ft_putstr_fd("minishell: ambiguous redirect: ", STDERR_FILENO);
		ft_putendl_fd(redirect->value.filename, STDERR_FILENO);
		dispose_wordlist(word);
		return (SYSTEM_ERR);
	}
	fd = -1;
	if (redirect->type == RT_INPUT)
		fd = open(word->word, O_RDONLY);
	else if (redirect->type == RT_OVERWRITE)
		fd = open(word->word, O_WRONLY | O_CREAT | O_TRUNC, 420);
	else if (redirect->type == RT_APPEND)
		fd = open(word->word, O_WRONLY | O_CREAT | O_APPEND, 420);
	dispose_wordlist(word);
	if (fd != -1)
		return (fd);
	perror("minishell");
	return (SYSTEM_ERR);
}

static int	do_redirect_heredoc(t_minishell *shell, t_redirect *redirect)
{
	int		fd;
	char	filename[18];
	char	*docment;

	ft_strcpy(filename, "/tmp/shtmp.XXXXXX");
	fd = ft_mkstemp(filename);
	if (fd == -1)
	{
		perror("minishell: ft_mksdtemp");
		return (SYSTEM_ERR);
	}
	docment = redirect->value.document->document;
	if (!redirect->value.document->quoted)
		docment = shell_expand_string(shell, docment, 1);
	ft_putstr_fd(docment, fd);
	if (!redirect->value.document->quoted)
		free(docment);
	close(fd);
	fd = open(filename, O_RDONLY);
	unlink(filename);
	if (fd != -1)
		return (fd);
	perror("minishell: open");
	return (SYSTEM_ERR);
}
