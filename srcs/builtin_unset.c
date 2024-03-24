/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:02:37 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 15:49:52 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "variable.h"
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

int	builtin_unset(t_minishell *shell, t_wordlist *wordlist)
{
	int		status;
	char	*temp;

	status = EXIT_SUCCESS;
	while (wordlist)
	{
		temp = wordlist->word;
		if (ft_strchr(temp, '=') || legal_identifier(temp))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd("unset: not a valid identifier: ", STDERR_FILENO);
			ft_putendl_fd(temp, STDERR_FILENO);
			status = EXIT_FAILURE;
		}
		else
			unbind_variable(shell, temp);
		wordlist = wordlist->next;
	}
	return (status);
}
