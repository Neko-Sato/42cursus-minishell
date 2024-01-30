/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 03:12:06 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/31 04:01:36 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <stddef.h>
#include <stdio.h>

int	get_lexical(t_minishell *gvars, char **line, size_t *pos, char **result)
{
	size_t	start;
	int		c;
	int		ret;

	if (skip_space(gvars, line, pos))
		return (-1);
	start = *pos;
	while (1)
	{
		c = pgetc(gvars, line, pos);
		if (ft_isspace(c) || ft_strchar("<>&|", c))
			break ;
		ret = 0;
		if (c == '\'')
			ret = skip_singlquote(gvars, line, pos);
		else if (c == '"')
			ret = skip_doublequote(gvars, line, pos);
		else if (c == '\\')
			ret = skip_backslash(gvars, line, pos);
		if (ret)
			return (ret);
		(*pos)++;
	}
	*result = ft_substr(*line, start, *pos - start);
	return (0);
}

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
		if (c == '\'')
			break ;
		if (c == '\0')
		{
			ft_putendl_fd("minishell: unmatched `'`", STDERR_FILENO);
			return (1);
		}
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
		if (c == '\0')
		{
			ft_putendl_fd("minishell: unmatched `\"`", STDERR_FILENO);
			return (1);
		}
		if (c == '\\')
		{
			(*pos)++;
			if (skip_backslash(gvars, line, pos))
				return (-1);
		}
		(*pos)++;
	}
	return (0);
}
