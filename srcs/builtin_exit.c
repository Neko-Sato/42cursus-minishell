/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:02:24 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 16:05:44 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

static int	get_last_status(t_wordlist *wordlist);

int	builtin_exit(t_minishell *shell, t_wordlist *wordlist)
{
	if (shell->isinteractive)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	shell->isinteractive = 0;
	shell->eof_reached = 1;
	return (get_last_status(wordlist));
}

static int	get_last_status(t_wordlist *wordlist)
{
	if (wordlist)
	{
		if (ft_isnumber(wordlist->word, 1))
		{
			if (wordlist->next)
			{
				ft_putstr_fd("minishell: exit: too many arguments\n",
					STDERR_FILENO);
				return (EXIT_FAILURE);
			}
			else
				return (ft_atoi(wordlist->word));
		}
		else
		{
			ft_putstr_fd("minishell: exit: numeric argument required: ",
				STDERR_FILENO);
			ft_putendl_fd(wordlist->word, STDERR_FILENO);
			return (2);
		}
	}
	return (EXIT_SUCCESS);
}
