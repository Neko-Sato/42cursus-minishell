/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 00:28:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/20 00:46:39 by hshimizu         ###   ########.fr       */
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
	if (ret)
		return (ret);
	parser->command = NULL;
	if (element.wordlist || element.redirect)
	{
		parser->command = make_simplecom(&element);
		if (!parser->command)
		{
			dispose_wordlist(element.wordlist);
			dispose_redirect(element.redirect);
			return (-1);
		}
	}
	return (0);
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
		return (1);
	parser->command = make_groupcom(temp);
	if (!parser->command)
	{
		dispose_command(parser->command);
		return (-1);
	}
	if (parser->token.type != TK_CLOSE_PAREN)
		return (1);
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
		return (1);
	type = parser->token.type - TK_PIPE;
	ret = lexer(shell, &parser->token);
	if (ret)
		return (ret);
	temp = parser->command;
	ret = take_subcom(shell, parser, type == CCT_PIPE, &next);
	if (ret)
		return (ret);
	if (!next)
		return (1);
	temp = make_conncom(type, parser->command, next);
	if (!temp)
	{
		dispose_command(next);
		return (-1);
	}
	parser->command = temp;
	return (0);
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
