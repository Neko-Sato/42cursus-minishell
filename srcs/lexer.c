/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:56:29 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/10 15:29:20 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"
#include <libft.h>
#include <stdlib.h>

static int	take_word(t_lexer *lexer);
static int	take_token(t_lexer *lexer);

int	lexer(char *line, t_lexical **result)
{
	int		ret;
	t_lexer	lexer;

	*result = NULL;
	lexer.line = line;
	lexer.pos = 0;
	lexer.next_lexical = result;
	ret = 0;
	while (!ret && lexer.line[lexer.pos])
	{
		skip_space(&lexer);
		ret = take_word(&lexer);
		if (ret)
			break ;
		ret = take_token(&lexer);
		if (ret)
			break ;
	}
	if (ret)
	{
		dispose_lexical(*result);
		*result = NULL;
	}
	return (ret);
}

void	dispose_lexical(t_lexical *lexical)
{
	t_lexical	*temp;

	while (lexical)
	{
		temp = lexical->next;
		free(lexical->value);
		free(lexical);
		lexical = temp;
	}
}

static int	take_word(t_lexer *lexer)
{
	t_lexical	*temp;
	char		*word;
	size_t		start;

	start = lexer->pos;
	if (skip_word(lexer))
		return (1);
	if (start == lexer->pos)
		return (0);
	word = ft_substr(lexer->line, start, lexer->pos - start);
	if (!word)
		return (-1);
	temp = malloc(sizeof(*temp));
	if (!temp)
	{
		free(word);
		return (-1);
	}
	temp->next = NULL;
	temp->token = TK_WORD;
	temp->value = word;
	*lexer->next_lexical = temp;
	lexer->next_lexical = &temp->next;
	return (0);
}

static int	take_token(t_lexer *lexer)
{
	t_lexical	*temp;
	t_token		token;

	token = match_token(&lexer->line[lexer->pos]);
	if (!token)
		return (0);
	lexer->pos += (int []){0, 0, 1, 2, 1, 2, 1, 2, 2, 1, 1}[token];
	temp = malloc(sizeof(*temp));
	if (!temp)
		return (-1);
	temp->next = NULL;
	temp->token = token;
	temp->value = NULL;
	*lexer->next_lexical = temp;
	lexer->next_lexical = &temp->next;
	return (0);
}
