/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 00:28:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/29 02:24:32 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "parser.h"
#include "shell.h"
#include "token.h"

static int	take_subcom(t_minishell *shell, int level, t_command **subcom);

int	take_groupcom(t_minishell *shell)
{
	int			ret;
	t_command	*temp;

	shell->brackets_level++;
	ret = take_subcom(shell, 0, &temp);
	if (ret == FATAL_ERR || ret == INTERRUPT)
		return (ret);
	shell->command = make_groupcom(temp);
	if (!shell->command)
	{
		dispose_command(temp);
		return (FATAL_ERR);
	}
	if (!temp)
		return (SYNTAX_ERR);
	if (ret)
		return (ret);
	shell->brackets_level--;
	return (lexer(shell));
}

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
	ret = take_subcom(shell, (type == CCT_PIPE) + 1, &next);
	if (ret == FATAL_ERR || ret == INTERRUPT)
		return (ret);
	temp = make_conncom(type, shell->command, next);
	if (!temp)
	{
		dispose_command(next);
		return (FATAL_ERR);
	}
	shell->command = temp;
	if (!next)
		return (SYNTAX_ERR);
	return (ret);
}

static int	take_subcom(t_minishell *shell, int level, t_command **subcom)
{
	int			ret;
	t_command	*temp;

	temp = shell->command;
	shell->command = NULL;
	if (level == 0)
		ret = take_top_command(shell);
	else if (level == 1)
		ret = take_command(shell);
	else
		ret = take_blockcom(shell);
	*subcom = shell->command;
	shell->command = temp;
	return (ret);
}
