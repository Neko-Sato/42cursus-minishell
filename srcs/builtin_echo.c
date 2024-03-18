/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:44:32 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 08:18:03 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define END "\n"
#define SPACER " "

static int	just_echo(char *arry[], int flag);

int	builtin_echo(int argc, char *argv[])
{
	int	flag;

	(void)argc;
	flag = 0;
	argv++;
	while (*argv)
	{
		if (!ft_strcmp("-n", *argv))
			flag |= 0b1;
		else
			break ;
		argv++;
	}
	if (just_echo(argv, flag))
	{
		perror("minishell: echo:");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	just_echo(char *arry[], int flag)
{
	while (*arry)
	{
		if (write(STDOUT_FILENO, *arry, ft_strlen(*arry)) == -1)
			return (-1);
		if (!*++arry)
			break ;
		if (write(STDOUT_FILENO, SPACER, 1) == -1)
			return (-1);
	}
	if (!(flag & 0b1))
		if (write(STDOUT_FILENO, END, 1) == -1)
			return (-1);
	return (0);
}
