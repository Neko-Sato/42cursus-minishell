/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:02:24 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/30 03:26:49 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

static int	set_last_status(t_minishell *shell, t_wordlist *wordlist);

int	builtin_exit(t_minishell *shell, t_wordlist *wordlist)
{
	if (shell->isinteractive)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (set_last_status(shell, wordlist))
		return (EXIT_FAILURE);
	shell->isinteractive = 0;
	shell->exit_immediately = 1;
	return (shell->last_status);
}

static int	set_last_status(t_minishell *shell, t_wordlist *wordlist)
{
	if (wordlist)
	{
		if (ft_isnumber(wordlist->word, 1))
		{
			if (wordlist->next)
			{
				ft_putstr_fd("minishell: exit: too many arguments\n",
					STDERR_FILENO);
				return (1);
			}
			else
				shell->last_status = (unsigned char)ft_atoi(wordlist->word);
		}
		else
		{
			ft_putstr_fd("minishell: exit: numeric argument required: ",
				STDERR_FILENO);
			ft_putendl_fd(wordlist->word, STDERR_FILENO);
			shell->last_status = 2;
		}
	}
	else
		shell->last_status = EXIT_SUCCESS;
	return (0);
}
