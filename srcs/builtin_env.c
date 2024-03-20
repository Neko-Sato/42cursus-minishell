/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:44:32 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/20 17:50:10 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	builtin_env(t_minishell *shell, t_wordlist *wordlist)
{
	int		temp;
	size_t	i;

	(void)wordlist;
	i = 0;
	while (shell->envp[i])
	{
		temp = write(STDOUT_FILENO, shell->envp[i],
				ft_strlen(shell->envp[i])) == -1;
		temp = temp || (write(STDOUT_FILENO, "\n", 1) == -1);
		if (temp)
		{
			perror("minishell: env");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
