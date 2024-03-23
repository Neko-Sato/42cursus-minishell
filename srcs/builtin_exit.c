/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:02:24 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 00:14:04 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

static int	get_status(t_minishell *shell, t_wordlist *wordlist);

int	builtin_exit(t_minishell *shell, t_wordlist *wordlist)
{
	if (shell->isinteractive)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(get_status(shell, wordlist));
	return (EXIT_FAILURE);
}

static int	get_status(t_minishell *shell, t_wordlist *wordlist)
{
	int	status;

	if (wordlist)
	{
		if (ft_isnumber(wordlist->word, 1))
		{
			status = ft_atoi(wordlist->word);
			if (wordlist->next)
			{
				ft_putstr_fd("minishell: exit: too many arguments\n",
					STDERR_FILENO);
				status = EXIT_FAILURE;
			}
		}
		else
		{
			ft_putstr_fd("minishell: exit: numeric argument required: ",
				STDERR_FILENO);
			ft_putendl_fd(wordlist->word, STDERR_FILENO);
			status = 2;
		}
	}
	else
		status = shell->last_status;
	return (status);
}
