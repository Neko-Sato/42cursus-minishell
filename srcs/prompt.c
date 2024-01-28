/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 23:17:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/28 21:41:15 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "repl.h"
#include <libft.h>
#include <readline.h>
#include <stdlib.h>

static char	*add_line(char *line, char *new_line);

int	put_prompt(t_minishell *gvars, t_repl *vars)
{
	char	*temp;
	char	*next;

	if (!vars->line)
		vars->line = readline((char *[]){PS1, NULL}[!gvars->isinteractive]);
	else
	{
		temp = vars->line;
		next = readline((char *[]){PS2, NULL}[!gvars->isinteractive]);
		if (next)
			vars->line = add_line(temp, next);
		free(temp);
		free(next);
	}
	if (!vars->line)
		return (-1);
	return (0);
}

static char	*add_line(char *line, char *new_line)
{
	char	*ret;
	size_t	size;

	if (!line || !new_line)
		return (NULL);
	size = ft_strlen(line) + ft_strlen(new_line) + 2;
	ret = (char *)malloc(sizeof(char) * size);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, line, size);
	ft_strlcpy(ret, "\n", size);
	ft_strlcpy(ret, new_line, size);
	return (ret);
}
