/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 00:00:08 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/24 22:48:05 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	put_prompt(t_minishell *vars);

reader_loop(vars)
{
	while (1)
	{
	}
}

int	read_command(t_minishell *vars)
{
	vars->pos = 0;
	vars->line = NULL;
	put_prompt(vars);
	while (vars->line[vars->pos] != '\n')
	{
		if (vars->line[vars->pos] == '\0')
		{
			put_prompt(vars);
			continue ;
		}
		if (//ここで処理)
			return (-1);
		pos++;
	}
	free(line);
	return (0);
}

/*
lineがNULLならprimarypromptでreadline
値があればセカンダリーpromptでreadlineしjoinする
*/
int	put_prompt(t_minishell *vars)
{
	char	*temp;
	char	*next;

	if (!vars->line)
		vars->line = readline(PS1);
	else
	{
		temp = vars->line;
		next = readline(PS2);
		if (next)
			vars->line = ft_strjoin(temp, next);
		else
			vars->line = NULL;
		free(temp);
		free(next);
	}
	if (!vars->line)
		return (-1);
	return (0);
}
