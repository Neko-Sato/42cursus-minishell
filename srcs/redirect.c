/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:20:56 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/23 20:53:29 by hshimizu         ###   ########.fr       */
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

static int	do_redirect_input(t_minishell *shell, t_redirect *redirect);
static int	do_redirect_heredoc(t_minishell *shell, t_redirect *redirect);

int	do_redirect(t_minishell *shell, t_redirect *redirect)
{
	int	ret;

	ret = 0;
	while (!ret && redirect)
	{
		if (redirect->type == RT_INPUT || redirect->type == RT_HEREDOC)
			ret = do_redirect_in(shell, redirect);
		else if (redirect->type == RT_OVERWRITE || redirect->type == RT_APPEND)
			ret = do_redirect_out(shell, redirect);
		redirect = redirect->next;
	}
	return (ret);
}

int	do_redirect_in(t_minishell *shell, t_redirect *redirect)
{
	int	fd;

	if (!redirect)
		return (0);
	if (redirect->type == RT_INPUT)
		fd = do_redirect_input(shell, redirect);
	else if (redirect->type == RT_HEREDOC)
		fd = do_redirect_heredoc(shell, redirect);
	else
		return (0);
	if (fd == -1)
		return (-1);
	if (fd == -2)
		return (1);
	return (-(dup2(fd, STDIN_FILENO) == -1));
}

static int	do_redirect_input(t_minishell *shell, t_redirect *redirect)
{
	int			fd;
	t_wordlist	*word;

	if (shell_expand_word(shell, redirect->value.filename, &word))
		return (-1);
	if (!word || word->next)
	{
		ft_putstr_fd("minishell: ambiguous redirect", STDERR_FILENO);
		dispose_wordlist(word);
		return (-2);
	}
	fd = open(word->word, O_RDONLY);
	dispose_wordlist(word);
	if (fd == -1)
	{
		perror("minishell");
		return (-2);
	}
	return (fd);
}

static int	do_redirect_heredoc(t_minishell *shell, t_redirect *redirect)
{
	int		fd;
	char	filename[18];
	char	*docment;

	ft_strcpy(filename, "/tmp/shtmp.XXXXXX");
	fd = ft_mkstemp(filename);
	if (fd == -1)
		return (-1);
	docment = redirect->value.document->document;
	if (!redirect->value.document->quoted)
		docment = shell_expand_string(shell, docment, 1);
	ft_putstr_fd(docment, fd);
	if (!redirect->value.document->quoted)
		free(docment);
	close(fd);
	fd = open(filename, O_RDONLY);
	unlink(filename);
	if (fd == -1)
		return (-2);
	return (fd);
}

int	do_redirect_out(t_minishell *shell, t_redirect *redirect)
{
	int			fd;
	t_wordlist	*word;

	if (!redirect)
		return (0);
	if (shell_expand_word(shell, redirect->value.filename, &word))
		return (-1);
	if (!word || word->next)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", STDERR_FILENO);
		dispose_wordlist(word);
		return (1);
	}
	if (redirect->type == RT_OVERWRITE)
		fd = open(word->word, O_WRONLY | O_CREAT | O_TRUNC, 420);
	else
		fd = open(word->word, O_WRONLY | O_CREAT | O_APPEND, 420);
	dispose_wordlist(word);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	return (-(dup2(fd, STDOUT_FILENO) == -1));
}
