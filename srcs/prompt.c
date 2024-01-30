/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 23:17:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/31 00:26:31 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <readline/readline.h>
#include <stdlib.h>

char	*put_prompt(t_minishell *gvars, char *line)
{
	char	*temp;
	char	*next;

	if (!line)
		line = readline((char *[]){PS1, NULL}[!gvars->isinteractive]);
	else
	{
		next = readline((char *[]){PS2, NULL}[!gvars->isinteractive]);
		if (next)
			line = add_line(line, next);
		free(next);
	}
	return (line);
}

int	pgetc(t_minishell *gvars, char **line, size_t pos)
{
	char	*temp;

	if (!*line || !(*line)[pos])
	{
		temp = put_prompt(gvars, *line);
		free(*line);
		*line = temp;
		if (!*line)
			return (-1);
	}
	return (line[pos]);
}
