/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 00:28:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/23 05:32:54 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "parser.h"
#include "shell.h"

static int	take_subcom(t_minishell *shell, t_parser *parser, int block,
				t_command **subcom);

int	take_simplecom(t_minishell *shell, t_parser *parser)
{
	int			ret;
	t_element	element;

	ret = take_element(shell, parser, &element);
	if (ret == SYSTEM_ERR || ret == INTERRUPT)
		return (ret);
	parser->command = NULL;
	if (element.wordlist || element.redirect)
	{
		parser->command = make_simplecom(&element);
		if (!parser->command)
		{
			dispose_wordlist(element.wordlist);
			dispose_redirect(element.redirect);
			ret = SYSTEM_ERR;
		}
	}
	return (ret);
}

int	take_groupcom(t_minishell *shell, t_parser *parser)
{
	int			ret;
	t_command	*temp;

	parser->brackets_level++;
	ret = take_subcom(shell, parser, 0, &temp);
	if (ret)
		return (ret);
	if (!temp)
		return (SYNTAX_ERR);
	parser->command = make_groupcom(temp);
	if (!parser->command)
	{
		dispose_command(parser->command);
		return (SYSTEM_ERR);
	}
	if (parser->token.type != TK_CLOSE_PAREN)
		return (SYNTAX_ERR);
	parser->brackets_level--;
	return (lexer(shell, &parser->token));
}

int	take_concom(t_minishell *shell, t_parser *parser)
{
	int				ret;
	t_concomtype	type;
	t_command		*temp;
	t_command		*next;

	if (!parser->command)
		return (SYNTAX_ERR);
	type = parser->token.type - TK_PIPE;
	ret = lexer(shell, &parser->token);
	if (ret)
		return (ret);
	temp = parser->command;
	ret = take_subcom(shell, parser, type == CCT_PIPE, &next);
	if (ret)
		return (ret);
	if (!next)
		return (SYNTAX_ERR);
	temp = make_conncom(type, parser->command, next);
	if (!temp)
	{
		dispose_command(next);
		return (SYSTEM_ERR);
	}
	parser->command = temp;
	return (NOERR);
}

static int	take_subcom(t_minishell *shell, t_parser *parser, int block,
		t_command **subcom)
{
	int			ret;
	t_command	*temp;

	temp = parser->command;
	if (block)
		ret = take_blockcom(shell, parser);
	else
		ret = take_command(shell, parser);
	*subcom = parser->command;
	parser->command = temp;
	return (ret);
}
