/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:10:11 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/23 05:23:03 by hshimizu         ###   ########.fr       */
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
	temp = NULL;
	if (shell->string && !(ret == SYSTEM_ERR || ret == INTERRUPT))
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
	int	ret;

	ret = NOERR;
	if (!shell->string)
	{
		ret = put_prompt(shell);
		if (ret)
			return (ret);
	}
	if (shell->string)
		ret = parser(shell);
	else
		shell->eof_reached = 1;
	return (ret);
}