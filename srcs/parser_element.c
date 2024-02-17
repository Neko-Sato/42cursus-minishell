/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_element.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:01:19 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/17 20:07:26 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "token.h"
#include <libft.h>
#include <stdlib.h>

static int	take_word(t_parser *parser, t_wordlist ***wordlist_last);
static int	take_redirect(t_parser *parser, t_redirect ***redirect_last);
static int	take_heredoc(t_parser *parser, t_redirect *redirect);

int	take_element(t_parser *parser, t_wordlist **wordlist, t_redirect **redirect)
{
	int			ret;
	t_wordlist	**wordlist_last;
	t_redirect	**redirect_last;

	*wordlist = NULL;
	*redirect = NULL;
	wordlist_last = wordlist;
	redirect_last = redirect;
	ret = 0;
	while (!ret && parser->lexical)
	{
		if (parser->lexical->token == TK_WORD)
			ret = take_word(parser, &wordlist_last);
		else if (is_redirect_token(parser->lexical->token))
			ret = take_redirect(parser, &redirect_last);
		else
			break ;
	}
	if (!ret)
		return (0);
	dispose_wordlist(*wordlist);
	dispose_redirect(*redirect);
	*wordlist = NULL;
	*redirect = NULL;
	return (ret);
}

static int	take_word(t_parser *parser, t_wordlist ***wordlist_last)
{
	t_wordlist	*wordlist;

	wordlist = malloc(sizeof(t_wordlist));
	if (!wordlist)
		return (-1);
	wordlist->next = NULL;
	wordlist->word = ft_strdup(parser->lexical->value);
	if (!wordlist->word)
	{
		free(wordlist);
		return (-1);
	}
	**wordlist_last = wordlist;
	*wordlist_last = &wordlist->next;
	parser->lexical = parser->lexical->next;
	return (0);
}

static int	take_redirect(t_parser *parser, t_redirect ***redirect_last)
{
	t_redirecttype	type;
	t_redirect		*redirect;

	type = parser->lexical->token - 2;
	parser->lexical = parser->lexical->next;
	if (!parser->lexical || parser->lexical->token != TK_WORD)
		return (1);
	redirect = malloc(sizeof(t_redirect));
	if (!redirect)
		return (-1);
	redirect->next = NULL;
	redirect->type = type;
	redirect->word = ft_strdup(parser->lexical->value);
	if (!redirect->word
		|| (type == RT_HEREDOC && take_heredoc(parser, redirect)))
	{
		free(redirect);
		return (-1);
	}
	**redirect_last = redirect;
	*redirect_last = &redirect->next;
	parser->lexical = parser->lexical->next;
	return (0);
}

static int	take_heredoc(t_parser *parser, t_redirect *redirect)
{
	t_heredoc	*heredoc;

	heredoc = malloc(sizeof(t_heredoc));
	if (!heredoc)
		return (-1);
	heredoc->next = NULL;
	heredoc->contents = NULL;
	heredoc->eof = redirect->word;
	*parser->heredoc = heredoc;
	parser->heredoc = &heredoc->next;
	return (0);
}
