/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 23:17:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/02 12:59:57 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include <libft.h>
#include <readline/readline.h>
#include <stdlib.h>

static char	*strjoin_at_newline(char *line, char *new_line);

int			interrupt_state = 0;

char	*put_primary_prompt(t_minishell *gvars)
{
	char	*line;

	if (gvars->isinteractive)
		line = readline(PS1);
	else
		line = readline(NULL);
	return (line);
}

char	*put_secondary_prompt(t_minishell *gvars, char *line)
{
	char	*old_line;
	char	*new_line;

	old_line = line;
	if (gvars->isinteractive)
		new_line = readline(PS2);
	else
		new_line = readline(NULL);
	if (!old_line)
		return (new_line);
	if (!new_line)
		return (old_line);
	line = strjoin_at_newline(old_line, new_line);
	free(old_line);
	free(new_line);
	return (line);
}

static char	*strjoin_at_newline(char *line, char *new_line)
{
	char	*ret;
	size_t	size;

	size = ft_strlen(line) + ft_strlen(new_line) + 2;
	ret = (char *)malloc(sizeof(char) * size);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, line, size);
	ft_strlcat(ret, "\n", size);
	ft_strlcat(ret, new_line, size);
	return (ret);
}
