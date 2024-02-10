/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:44:32 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/09 08:35:49 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>

#define END "\n"
#define SPACER " "

int	builtin_echo(int argc, char *argv[])
{
	int	flag;

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
	while (*argv)
	{
		ft_putstr_fd(*argv++, STDOUT_FILENO);
		if (!*argv)
			break ;
		ft_putstr_fd(SPACER, STDOUT_FILENO);
	}
	if (!(flag & 0b1))
		ft_putstr_fd(END, STDOUT_FILENO);
	return (0);
}
