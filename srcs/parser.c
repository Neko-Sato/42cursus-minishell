/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:34:56 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/23 05:48:09 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "lexer.h"
#include "parser.h"
#include "shell.h"
#include <libft.h>
#include <unistd.h>

int	parser(t_minishell *shell)
{
	int			syntaxerr;
	int			ret;
	t_parser	parser;

	while (1)
	{
		ft_bzero(&parser, sizeof(parser));
		parser.heredoc_last = &parser.heredoc;
		ret = lexer(shell, &parser.token);
		if (ret)
			break ;
		ret = take_command(shell, &parser);
		shell->command = parser.command;
		shell->heredoc = parser.heredoc;
		break ;
	}
	if (ret == SYSTEM_ERR || ret == INTERRUPT)
		return (ret);
	syntaxerr = (ret == SYNTAX_ERR);
	while (!ft_strchr("\n", shell->string[shell->sindex]))
		shell->sindex++;
	ret = gather_heredoc(shell);
	if (!ret && syntaxerr)
		ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
	return (ret);
}

int	take_command(t_minishell *shell, t_parser *parser)
{
	int	ret;

	if (parser->token.type == TK_OPEN_PAREN)
	{
		ret = lexer(shell, &parser->token);
		if (ret)
			return (ret);
		ret = take_groupcom(shell, parser);
	}
	else
		ret = take_blockcom(shell, parser);
	if (ret)
		return (ret);
	if (parser->token.type == TK_EOL)
		return (NOERR);
	if (parser->token.type == TK_AND || parser->token.type == TK_OR)
		ret = take_concom(shell, parser);
	else if (!parser->brackets_level || parser->token.type != TK_CLOSE_PAREN)
		ret = SYNTAX_ERR;
	return (ret);
}

int	take_blockcom(t_minishell *shell, t_parser *parser)
{
	int	ret;

	ret = take_simplecom(shell, parser);
	if (ret)
		return (ret);
	if (parser->token.type == TK_EOL)
		return (NOERR);
	if (parser->token.type == TK_PIPE)
		ret = take_concom(shell, parser);
	return (ret);
}
