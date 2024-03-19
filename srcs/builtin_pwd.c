/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:02:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 22:29:19 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	builtin_pwd(t_minishell *shell, t_wordlist *wordlist)
{
	char *current_path;

	(void)shell;
	(void)wordlist;
	current_path = getcwd(NULL, 0);
	if (!current_path)
	{
		perror("minishell: pwd: ");
		return (1);
	}
	ft_putendl_fd(current_path, 1);
	free(current_path);
	return (0);
}
