/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:34:56 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 16:13:06 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "lexer.h"
#include "parser.h"
#include "shell.h"
#include "token.h"
#include <libft.h>
#include <unistd.h>

int	parser(t_minishell *shell)
{
	int	syntaxerr;
	int	ret;

	shell->brackets_level = 0;
	ret = lexer(shell);
	if (!ret)
		ret = take_command(shell);
	if (ret == FATAL_ERR || ret == INTERRUPT)
		return (ret);
	syntaxerr = (ret == SYNTAX_ERR);
	while (shell->string && !ft_strchr("\n", shell->string[shell->sindex]))
		shell->sindex++;
	ret = gather_heredoc(shell);
	if (!ret && syntaxerr)
	{
		ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
		shell->last_status = 2;
		return (SYNTAX_ERR);
	}
	return (ret);
}

int	take_command(t_minishell *shell)
{
	int	ret;

	if (shell->token.type == TK_OPEN_PAREN)
	{
		ret = lexer(shell);
		if (ret)
			return (ret);
		ret = take_groupcom(shell);
	}
	else
		ret = take_blockcom(shell);
	if (ret)
		return (ret);
	if (shell->token.type == TK_EOL)
		return (NOERR);
	if (shell->token.type == TK_AND || shell->token.type == TK_OR)
		ret = take_concom(shell);
	else if (!shell->brackets_level || shell->token.type != TK_CLOSE_PAREN)
		ret = SYNTAX_ERR;
	return (ret);
}

int	take_blockcom(t_minishell *shell)
{
	int	ret;

	ret = take_simplecom(shell);
	if (ret)
		return (ret);
	if (shell->token.type == TK_EOL)
		return (NOERR);
	if (shell->token.type == TK_PIPE)
		ret = take_concom(shell);
	return (ret);
}
