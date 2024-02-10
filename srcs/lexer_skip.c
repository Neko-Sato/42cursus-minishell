/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_skip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:04:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/10 15:29:26 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"
#include <libft.h>

static int	skip_singlquote(t_lexer *lexer);
static int	skip_doublequote(t_lexer *lexer);

int	skip_space(t_lexer *lexer)
{
	int	c;

	while (1)
	{
		c = lexer->line[lexer->pos];
		if (c == '\0' || !ft_isspace(c))
			break ;
		lexer->pos++;
	}
	return (0);
}

int	skip_word(t_lexer *lexer)
{
	int	ret;
	int	c;

	while (1)
	{
		if (match_token(&lexer->line[lexer->pos]))
			break ;
		c = lexer->line[lexer->pos];
		if (c == '\0' || ft_isspace(c))
			break ;
		lexer->pos++;
		ret = 0;
		if (c == '\'')
			ret = skip_singlquote(lexer);
		else if (c == '"')
			ret = skip_doublequote(lexer);
		if (ret)
			return (1);
	}
	return (0);
}

static int	skip_singlquote(t_lexer *lexer)
{
	int	c;

	while (1)
	{
		c = lexer->line[lexer->pos];
		if (c == '\0')
		{
			ft_putstr_fd("minishell: unmatched `'`\n", 2);
			return (1);
		}
		lexer->pos++;
		if (c == '\'')
			return (0);
	}
}

static int	skip_doublequote(t_lexer *lexer)
{
	int	c;

	while (1)
	{
		c = lexer->line[lexer->pos];
		if (c == '\0')
		{
			ft_putstr_fd("minishell: unmatched `\"`\n", 2);
			return (1);
		}
		lexer->pos++;
		if (c == '"')
			return (0);
	}
}
