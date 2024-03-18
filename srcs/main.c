/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 07:42:02 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 07:42:36 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	shell;
	int			ret;

	(void)argc;
	(void)argv;
	shell_init(&shell, envp);
	ret = reader_loop(&shell);
	shell_deinit(&shell);
	return (ret);
}
