/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:10:11 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/22 00:07:45 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shell.h"
#include <history.h>
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

int	read_command(t_minishell *shell)
{
	char	*temp;
	int		ret;

	ret = parse_command(shell);
	if (ret == SYNTAX_ERR)
		ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
	temp = NULL;
	if (shell->string && ret != INTERRUPT)
	{
		if (shell->string[shell->sindex])
		{
			shell->sindex++;
			temp = ft_strdup(&shell->string[shell->sindex]);
			if (!temp)
				return (SYSTEM_ERR);
			shell->string[shell->sindex] = '\0';
		}
		if (shell->isinteractive && *shell->string)
			add_history(shell->string);
	}
	free(shell->string);
	shell->string = temp;
	shell->sindex = 0;
	return (ret);
}

int	parse_command(t_minishell *shell)
{
	int	syntaxerr;
	int	ret;

	ret = NOERR;
	if (!shell->string)
		ret = put_prompt(shell);
	if (ret)
		return (ret);
	if (shell->string)
	{
		ret = parser(shell);
		syntaxerr = (ret == SYNTAX_ERR);
		if (!syntaxerr && ret)
			return (ret);
		ret = gather_heredoc(shell);
		if (ret)
			return (ret);
		if (syntaxerr)
			ret = SYNTAX_ERR;
	}
	else
		shell->eof_reached = 1;
	return (ret);
}
