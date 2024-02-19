/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_element.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:01:19 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/20 03:26:16 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "token.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

static int	take_word(t_minishell *shell, t_parser *parser,
				t_wordlist ***wordlist_last);
static int	take_redirect(t_minishell *shell, t_parser *parser,
				t_redirect ***redirect_last);
static int	take_heredoc(t_parser *parser, t_redirect *redirect);

int	take_element(t_minishell *shell, t_parser *parser, t_element *element)
{
	int			ret;
	t_wordlist	**wordlist_last;
	t_redirect	**redirect_last;

	ft_bzero(element, sizeof(*element));
	wordlist_last = &element->wordlist;
	redirect_last = &element->redirect;
	ret = NOERR;
	while (!ret)
	{
		if (parser->token.type == TK_WORD)
			ret = take_word(shell, parser, &wordlist_last);
		else if (is_redirect_token(parser->token.type))
			ret = take_redirect(shell, parser, &redirect_last);
		else
			break ;
	}
	if (!ret)
		return (NOERR);
	dispose_wordlist(element->wordlist);
	dispose_redirect(element->redirect);
	ft_bzero(&element, sizeof(*element));
	return (ret);
}

static int	take_word(t_minishell *shell, t_parser *parser,
		t_wordlist ***wordlist_last)
{
	t_wordlist	*wordlist;

	wordlist = malloc(sizeof(t_wordlist));
	if (!wordlist)
		return (SYSTEM_ERR);
	wordlist->next = NULL;
	wordlist->word = parser->token.value;
	**wordlist_last = wordlist;
	*wordlist_last = &wordlist->next;
	return (lexer(shell, &parser->token));
}

static int	take_redirect(t_minishell *shell, t_parser *parser,
		t_redirect ***redirect_last)
{
	int				ret;
	t_redirecttype	type;
	t_redirect		*redirect;

	type = parser->token.type - TK_INPUT;
	ret = lexer(shell, &parser->token);
	if (ret)
		return (ret);
	if (parser->token.type != TK_WORD)
		return (SYNTAX_ERR);
	redirect = malloc(sizeof(t_redirect));
	if (!redirect)
		return (SYSTEM_ERR);
	redirect->next = NULL;
	redirect->type = type;
	redirect->word = parser->token.value;
	if (type == RT_HEREDOC && take_heredoc(parser, redirect))
	{
		free(redirect);
		return (SYSTEM_ERR);
	}
	**redirect_last = redirect;
	*redirect_last = &redirect->next;
	return (lexer(shell, &parser->token));
}

static int	take_heredoc(t_parser *parser, t_redirect *redirect)
{
	t_heredoc	*heredoc;

	heredoc = malloc(sizeof(t_heredoc));
	if (!heredoc)
		return (SYSTEM_ERR);
	heredoc->next = NULL;
	heredoc->contents = NULL;
	heredoc->eof = redirect->word;
	*parser->heredoc_last = heredoc;
	parser->heredoc_last = &heredoc->next;
	return (NOERR);
}
