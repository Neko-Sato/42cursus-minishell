/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_disk_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:29:01 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/13 18:32:45 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "shell.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	execute_disk_command(t_minishell *shell, t_execute vars)
{
	int		status;
	char	**temp;

	(void)shell;
	temp = wordlist2strarray(vars.wordlist);
	if (!temp)
		return (-1);
	ft_putstr_fd((char *[]){"async", "sync"}[!vars.already_fork], 2);
	ft_putnbr_fd(getpid(), 2);
	ft_putstr_fd(": ", 2);
	ft_putstrarry_fd(temp, ", ", 1);
	status = -!ft_strcmp("error", temp[0]);
	free(temp);
	return (status);
}
