/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:59:17 by hshimizu          #+#    #+#             */
/*   Updated: 2023/11/30 17:37:51 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <unistd.h>

int	main(int argc, char *argv[], char *envp[])
{
	int			ret;
	t_minishell	args;

	(void)argc;
	(void)argv;
	ret = minishell_init(&args, envp);
	if (!ret)
	{
		ret = repl(&args);
		minishell_destroy(&args);
	}
	else
		ft_putendl_fd("Error\n", STDERR_FILENO);
	return (ret);
}
