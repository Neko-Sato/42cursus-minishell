/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:02:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 17:06:30 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <errno.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	builtin_pwd(t_minishell *shell, t_wordlist *wordlist)
{
	int		err;
	char	*temp;

	(void)wordlist;
	if (!shell->cwd)
	{
		temp = getcwd(NULL, 0);
		if (!temp && errno == ENOMEM)
			return (FATAL_ERR);
		if (!temp)
		{
			perror("minishell: pwd");
			return (EXIT_FAILURE);
		}
		shell->cwd = temp;
	}
	err = write(STDOUT_FILENO, shell->cwd, ft_strlen(shell->cwd)) == -1;
	err = err || write(STDOUT_FILENO, "\n", 1) == -1;
	if (err)
	{
		perror("minishell: pwd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
