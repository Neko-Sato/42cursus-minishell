/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:02:24 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 00:18:54 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

static void	set_last_status(t_minishell *shell, t_wordlist *wordlist);

int	builtin_exit(t_minishell *shell, t_wordlist *wordlist)
{
	if (shell->isinteractive)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	set_last_status(shell, wordlist);
	exit(shell->last_status);
	return (EXIT_FAILURE);
}

static void	set_last_status(t_minishell *shell, t_wordlist *wordlist)
{
	if (wordlist)
	{
		if (ft_isnumber(wordlist->word, 1))
		{
			if (wordlist->next)
			{
				ft_putstr_fd("minishell: exit: too many arguments\n",
					STDERR_FILENO);
				shell->last_status = EXIT_FAILURE;
			}
			else
				shell->last_status = ft_atoi(wordlist->word);
		}
		else
		{
			ft_putstr_fd("minishell: exit: numeric argument required: ",
				STDERR_FILENO);
			ft_putendl_fd(wordlist->word, STDERR_FILENO);
			shell->last_status = 2;
		}
	}
}
