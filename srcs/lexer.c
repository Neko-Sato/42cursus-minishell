/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 03:12:06 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/31 03:12:31 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <stddef.h>

int	skip_space(t_minishell *gvars, char **line, size_t *pos)
{
	int	c;

	while (1)
	{
		c = pgetc(gvars, line, *pos);
		if (c == -1)
			return (-1);
		if (!c || ft_isspace(c))
			break ;
		(*pos)++;
	}
	return (0);
}

int	skip_backslash(t_minishell *gvars, char **line, size_t *pos)
{
	int	c;

	c = pgetc(gvars, line, *pos);
	if (c == -1)
		return (-1);
	(*pos)++;
	return (0);
}

int	skip_singlquote(t_minishell *gvars, char **line, size_t *pos)
{
	int	c;

	while (1)
	{
		c = pgetc(gvars, line, *pos);
		if (c == -1)
			return (-1);
		if (ft_strchr("'", c))
			break ;
		(*pos)++;
	}
	return (0);
}

int	skip_doublequote(t_minishell *gvars, char **line, size_t *pos)
{
	int	c;

	while (1)
	{
		c = pgetc(gvars, line, *pos);
		if (c == -1)
			return (-1);
		if (ft_strchr("\"", c))
			break ;
		else if (c == '\\')
		{
			(*pos)++;
			if (skip_backslash(gvars, line, pos))
				return (-1);
		}
		(*pos)++;
	}
	return (0);
}
