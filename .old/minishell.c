/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:10:54 by hshimizu          #+#    #+#             */
/*   Updated: 2023/12/18 04:53:23 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

static int	init(t_minishell *args, char *envp[]);
static void	destroy(t_minishell *args);

int	minishell_init(t_minishell *args, char *envp[])
{
	int	ret;

	ret = init(args, envp);
	if (ret)
		destroy(args);
	return (ret);
}

void	minishell_destroy(t_minishell *args)
{
	return (destroy(args));
}

static int	init(t_minishell *args, char *envp[])
{
	ft_bzero(args, sizeof(*args));
	rl_outstream = stderr;
	args->isinteractive = isatty(STDIN_FILENO);
	args->vars = ft_vector(sizeof(char *), (char *[]){NULL}, 1);
	if (!args->vars)
		return (-1);
	args->envp = ft_vector(sizeof(char *), (char *[]){NULL}, 1);
	if (!args->envp)
		return (-1);
	while (*envp)
		if (putvar(*envp++))
			return (-1);
	return (0);
}

static void	destroy(t_minishell *args)
{
	size_t	i;

	if (args->vars)
	{
		i = 0;
		while (args->vars[i])
			free(args->vars[i++]);
		ft_vector_del(args->vars);
	}
	if (args->envp)
	{
		i = 0;
		while (args->envp[i])
			free(args->envp[i++]);
		ft_vector_del(args->envp);
	}
}
