/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 19:43:32 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/01 02:49:40 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "variable.h"
#include <libft.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	init(t_minishell *gvars, char *envp[]);

int	minishell_init(t_minishell *gvars, char *envp[])
{
	if (init(gvars, envp))
	{
		minishell_destroy(gvars);
		return (-1);
	}
	return (0);
}

static int	init(t_minishell *gvars, char *envp[])
{
	rl_instream = stdin;
	rl_outstream = stderr;
	gvars->isinteractive = isatty(STDIN_FILENO) && isatty(STDERR_FILENO);
	if (gvars->isinteractive)
		rl_event_hook = (rl_hook_func_t *)ft_noop;
	gvars->vars = ft_vector(sizeof(char *), NULL, 0);
	if (!gvars->vars)
		return (-1);
	gvars->envp = ft_vector(sizeof(char *), (char *[]){NULL}, 1);
	if (!gvars->envp)
		return (-1);
	while (*envp)
		if (putvar(&gvars->envp, *envp++))
			return (-1);
	return (0);
}

void	minishell_destroy(t_minishell *gvars)
{
	(void)gvars;
}
