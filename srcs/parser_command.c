/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 00:28:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 15:08:23 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "parser.h"
#include "shell.h"
#include "token.h"

static int	take_subcom(t_minishell *shell, int block, t_command **subcom);

int	take_simplecom(t_minishell *shell)
{
	int			ret;
	t_element	element;

	shell->command = NULL;
	ret = take_element(shell, &element);
	if (ret == FATAL_ERR || ret == INTERRUPT)
		return (ret);
	if (element.wordlist || element.redirect)
	{
		shell->command = make_simplecom(&element);
		if (!shell->command)
		{
			dispose_wordlist(element.wordlist);
			dispose_redirect(element.redirect);
			return (FATAL_ERR);
		}
	}
	return (ret);
}

int	take_groupcom(t_minishell *shell)
{
	int			ret;
	t_command	*temp;

	shell->brackets_level++;
	ret = take_subcom(shell, 0, &temp);
	if (ret)
		return (ret);
	if (!temp)
		return (SYNTAX_ERR);
	shell->command = make_groupcom(temp);
	if (!shell->command)
	{
		dispose_command(temp);
		return (FATAL_ERR);
	}
	if (shell->token.type != TK_CLOSE_PAREN)
		return (SYNTAX_ERR);
	shell->brackets_level--;
	return (lexer(shell));
}

int	take_concom(t_minishell *shell)
{
	int				ret;
	t_concomtype	type;
	t_command		*temp;
	t_command		*next;

	if (!shell->command)
		return (SYNTAX_ERR);
	type = shell->token.type - TK_PIPE;
	ret = lexer(shell);
	if (ret)
		return (ret);
	ret = take_subcom(shell, type == CCT_PIPE, &next);
	if (ret == FATAL_ERR || ret == INTERRUPT)
		return (ret);
	if (!next)
		return (SYNTAX_ERR);
	temp = make_conncom(type, shell->command, next);
	if (!temp)
	{
		dispose_command(next);
		return (FATAL_ERR);
	}
	shell->command = temp;
	return (ret);
}

static int	take_subcom(t_minishell *shell, int block, t_command **subcom)
{
	int			ret;
	t_command	*temp;

	temp = shell->command;
	if (block)
		ret = take_blockcom(shell);
	else
		ret = take_command(shell);
	*subcom = shell->command;
	shell->command = temp;
	return (ret);
}
