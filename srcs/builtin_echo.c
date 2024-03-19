/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:44:32 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 18:28:57 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "n"
#define END "\n"
#define SPACER " "

#define DISPLAY_RETURN 0b01

static void	pretreatment(t_wordlist **wordlist, int *flag);
static int	just_echo(t_wordlist **wordlist, int *flag);

int	builtin_echo(t_minishell *shell, t_wordlist *wordlist)
{
	int	flag;

	(void)shell;
	pretreatment(&wordlist, &flag);
	if (just_echo(&wordlist, &flag))
	{
		perror("minishell: echo:");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	pretreatment(t_wordlist **wordlist, int *flag)
{
	size_t	i;
	char	*temp;

	*flag = 0;
	*wordlist = (*wordlist)->next;
	while (*wordlist && '-' == *(*wordlist)->word)
	{
		temp = (*wordlist)->word + 1;
		i = ft_strspn(temp, OPTIONS);
		if (!*temp || temp[i])
			break ;
		i = 0;
		while (temp[i])
		{
			if (temp[i] == 'n')
				*flag |= DISPLAY_RETURN;
			i++;
		}
		*wordlist = (*wordlist)->next;
	}
}

static int	just_echo(t_wordlist **wordlist, int *flag)
{
	while (*wordlist)
	{
		if (write(STDOUT_FILENO, (*wordlist)->word,
				ft_strlen((*wordlist)->word)) == -1)
			return (-1);
		*wordlist = (*wordlist)->next;
		if (!*wordlist)
			break ;
		if (write(STDOUT_FILENO, SPACER, 1) == -1)
			return (-1);
	}
	if (!(*flag & DISPLAY_RETURN))
		if (write(STDOUT_FILENO, END, 1) == -1)
			return (-1);
	return (0);
}
