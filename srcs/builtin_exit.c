/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:02:24 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/22 17:35:52 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

int	builtin_exit(t_minishell *shell, t_wordlist *wordlist)
{
	int	status;

	status = EXIT_SUCCESS;
	if (wordlist)
	{
		if (ft_isnumber(wordlist->word, 1))
			status = ft_atoi(wordlist->word);
		else
		{
			ft_putstr_fd("minishell: exit: numeric argument required: ",
				STDERR_FILENO);
			ft_putendl_fd(wordlist->word, STDERR_FILENO);
			status = 2;
		}
	}
	if (wordlist && wordlist->next)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		status = EXIT_FAILURE;
	}
	if (shell->isinteractive)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(status);
	return (EXIT_SUCCESS);
}
