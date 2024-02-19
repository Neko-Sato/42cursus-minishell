/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:56:29 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/20 01:39:31 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell.h"
#include "token.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

int	lexer(t_minishell *shell, t_token *token)
{
	int		ret;
	size_t	zindex;

	zindex = shell->sindex;
	ret = skip_space(shell, &zindex);
	if (ret)
		return (ret);
	shell->sindex = zindex;
	token->value = NULL;
	if (shell->string[zindex])
	{
		token->type = match_token(&shell->string[zindex]);
		zindex += (int []){0, 1, 1, 2, 1, 2, 1, 2, 2, 1, 1}[token->type];
		if (token->type == TK_WORD)
			ret = get_word(shell, &zindex, &token->value);
		if (ret)
			return (ret);
	}
	else
		token->type = TK_EOL;
	shell->sindex = zindex;
	return (0);
}

int	skip_space(t_minishell *shell, size_t *zindex)
{
	while (1)
	{
		if (!ft_isblank(shell->string[*zindex]))
			break ;
		(*zindex)++;
	}
	return (0);
}

int	get_word(t_minishell *shell, size_t *zindex, char **word)
{
	int	ret;

	ret = 0;
	while (1)
	{
		if (shell->string[*zindex] == '\0')
			break ;
		if (ft_isblank(shell->string[*zindex])
			|| match_token(&shell->string[*zindex]))
			break ;
		(*zindex)++;
		if (shell->string[*zindex - 1] == '\'')
			ret = skip_singlquote(shell, zindex);
		else if (shell->string[*zindex - 1] == '"')
			ret = skip_doublequote(shell, zindex);
		if (ret)
			return (ret);
	}
	if (*zindex == shell->sindex)
		return (0);
	*word = ft_substr(&shell->string[shell->sindex], 0, *zindex
			- shell->sindex);
	if (!*word)
		return (-1);
	return (0);
}

int	skip_singlquote(t_minishell *shell, size_t *zindex)
{
	int	ret;

	while (1)
	{
		if (shell->string[*zindex] == '\0')
		{
			ret = put_prompt(shell, PS2);
			if (ret)
				return (ret);
			if (shell->string[*zindex] == '\0')
			{
				ft_putstr_fd("minishell: unmatched `'`\n", STDERR_FILENO);
				return (1);
			}
		}
		(*zindex)++;
		if (shell->string[*zindex - 1] == '\'')
			return (0);
	}
}

int	skip_doublequote(t_minishell *shell, size_t *zindex)
{
	int	ret;

	while (1)
	{
		if (shell->string[*zindex] == '\0')
		{
			ret = put_prompt(shell, PS2);
			if (ret)
				return (ret);
			if (shell->string[*zindex] == '\0')
			{
				ft_putstr_fd("minishell: unmatched `\"`\n", STDERR_FILENO);
				return (1);
			}
		}
		(*zindex)++;
		if (shell->string[*zindex - 1] == '"')
			return (0);
	}
}
