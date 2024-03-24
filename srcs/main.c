/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 07:42:02 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 16:41:37 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	shell;
	int			ret;

	(void)argc;
	(void)argv;
	if (shell_init(&shell, envp))
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	ret = reader_loop(&shell);
	shell_deinit(&shell);
	return (ret);
}
