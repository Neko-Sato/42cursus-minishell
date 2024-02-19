/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:34:56 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/20 01:18:20 by hshimizu         ###   ########.fr       */
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
	int			ret;
	t_parser	parser;

	ret = put_prompt(shell, PS1);
	if (ret)
		return (ret);
	ft_bzero(&parser, sizeof(parser));
	parser.heredoc_last = &parser.heredoc;
	ret = lexer(shell, &parser.token);
	if (!ret)
		ret = take_command(shell, &parser);
	if (ret == 1)
		ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
	if (ret)
	{
		dispose_command(parser.command);
		dispose_heredoc(parser.heredoc);
		return (ret);
	}
	shell->command = parser.command;
	shell->heredoc = parser.heredoc;
	return (0);
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
		return (0);
	if (parser->token.type == TK_AND || parser->token.type == TK_OR)
		ret = take_concom(shell, parser);
	else if (!parser->brackets_level || parser->token.type != TK_CLOSE_PAREN)
		ret = 1;
	return (ret);
}

int	take_blockcom(t_minishell *shell, t_parser *parser)
{
	int	ret;

	ret = take_simplecom(shell, parser);
	if (ret)
		return (ret);
	if (parser->token.type == TK_EOL)
		return (0);
	if (parser->token.type == TK_PIPE)
		ret = take_concom(shell, parser);
	return (ret);
}
