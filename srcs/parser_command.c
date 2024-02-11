/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 00:28:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/11 12:06:58 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "lexer.h"
#include "parser.h"

static int	take_command_internal(t_parser *parser, t_command **command);
static int	take_blockcom(t_parser *parser, t_command **command);
static int	take_groupcom(t_parser *parser, t_command **command);
static int	take_concom(t_parser *parser, t_command **command);

int	take_command(t_parser *parser, t_command **command)
{
	int	ret;

	ret = take_command_internal(parser, command);
	if (ret)
	{
		dispose_command(*command);
		*command = NULL;
	}
	return (ret);
}

static int	take_command_internal(t_parser *parser, t_command **command)
{
	int	ret;

	if (!parser->lexical)
		return (0);
	if (parser->lexical->token == TK_OPEN_PAREN)
		ret = take_groupcom(parser, command);
	else
		ret = take_blockcom(parser, command);
	if (ret)
		return (ret);
	if (!parser->lexical)
		return (0);
	if (parser->lexical->token == TK_AND || parser->lexical->token == TK_OR)
		ret = take_concom(parser, command);
	else if (!parser->brackets_level
		|| parser->lexical->token != TK_CLOSE_PAREN)
		ret = 1;
	return (ret);
}

static int	take_blockcom(t_parser *parser, t_command **command)
{
	int			ret;
	t_command	*temp;
	t_wordlist	*wordlist;
	t_redirect	*redirect;

	*command = NULL;
	ret = take_element(parser, &wordlist, &redirect);
	if (ret)
		return (ret);
	if (wordlist || redirect)
	{
		temp = make_simplecom(wordlist, redirect);
		if (!temp)
		{
			dispose_wordlist(wordlist);
			dispose_redirect(redirect);
			return (-1);
		}
		*command = temp;
	}
	if (!parser->lexical)
		return (0);
	if (parser->lexical->token == TK_PIPE)
		ret = take_concom(parser, command);
	return (ret);
}

static int	take_groupcom(t_parser *parser, t_command **command)
{
	int			ret;
	t_command	*subcommand;

	*command = NULL;
	parser->brackets_level++;
	parser->lexical = parser->lexical->next;
	ret = take_command(parser, &subcommand);
	if (ret)
		return (ret);
	if (!subcommand)
		return (1);
	*command = make_groupcom(subcommand);
	if (!*command)
	{
		dispose_command(subcommand);
		return (-1);
	}
	if (!parser->lexical || parser->lexical->token != TK_CLOSE_PAREN)
		return (1);
	parser->brackets_level--;
	parser->lexical = parser->lexical->next;
	return (0);
}

static int	take_concom(t_parser *parser, t_command **command)
{
	int				ret;
	t_concomtype	type;
	t_command		*next;
	t_command		*temp;

	if (!*command)
		return (1);
	type = parser->lexical->token - 6;
	parser->lexical = parser->lexical->next;
	if (type == CCT_PIPE)
		ret = take_blockcom(parser, &next);
	else
		ret = take_command(parser, &next);
	if (ret)
		return (ret);
	if (!next)
		return (1);
	temp = make_conncom(type, *command, next);
	if (!temp)
	{
		dispose_command(next);
		return (-1);
	}
	*command = temp;
	return (0);
}
