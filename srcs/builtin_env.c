/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:44:32 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/22 10:21:30 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "variable.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	builtin_env(t_minishell *shell, t_wordlist *wordlist)
{
	int		err;
	size_t	i;
	char	**envp;

	(void)wordlist;
	i = 0;
	envp = get_envp(shell);
	if (!envp)
		return (-1);
	while (envp[i])
	{
		err = write(STDOUT_FILENO, envp[i], ft_strlen(envp[i])) == -1;
		err = err || (write(STDOUT_FILENO, "\n", 1) == -1);
		if (err)
			break ;
		i++;
	}
	ft_2darraydel(envp);
	if (err)
	{
		perror("minishell: env");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
