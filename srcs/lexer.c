/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 08:03:34 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/02 18:30:45 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"
#include <libft.h>
#include <stddef.h>

static int	skip_space(char **line, size_t *pos);
static int	skip_word(char **line, size_t *pos);
static int	skip_singlquote(char **line, size_t *pos);
static int	skip_doublequote(char **line, size_t *pos);

int	get_word(char **line, size_t *pos, char **result)
{
	int		ret;
	size_t	start;
	char	*temp;

	ret = skip_space(line, pos);
	if (ret)
		return (ret);
	start = *pos;
	ret = skip_word(line, pos);
	if (ret)
		return (ret);
	if (start == *pos)
		return (0);
	temp = ft_substr(*line, start, *pos - start);
	if (!temp)
		return (-1);
	*result = temp;
	return (0);
}

static int	skip_space(char **line, size_t *pos)
{
	int	c;

	while (1)
	{
		c = (*line)[*pos];
		if (c == '\0' || !ft_isspace(c))
			return (0);
		(*pos)++;
	}
}

static int	skip_word(char **line, size_t *pos)
{
	int	ret;
	int	c;

	while (1)
	{
		if (str2token(&(*line)[*pos]))
			return (0);
		c = (*line)[*pos];
		if (ft_isspace(c))
			return (0);
		(*pos)++;
		ret = 0;
		if (c == '\'')
			ret = skip_singlquote(line, pos);
		else if (c == '"')
			ret = skip_doublequote(line, pos);
		if (ret)
			return (ret);
	}
}

static int	skip_singlquote(char **line, size_t *pos)
{
	int	c;

	while (1)
	{
		c = (*line)[*pos];
		if (c == '\0')
		{
			ft_putstr_fd("minishell: unmatched `'`\n", 2);
			return (1);
		}
		(*pos)++;
		if (c == '\'')
			return (0);
	}
}

static int	skip_doublequote(char **line, size_t *pos)
{
	int	c;

	while (1)
	{
		c = (*line)[*pos];
		if (c == '\0')
		{
			ft_putstr_fd("minishell: unmatched `\"`\n", 2);
			return (1);
		}
		(*pos)++;
		if (c == '"')
			return (0);
	}
}
