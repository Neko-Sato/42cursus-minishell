/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_element.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:01:19 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 12:58:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "token.h"
#include <libft.h>
#include <stdlib.h>

static int	take_word(t_minishell *shell, t_wordlist ***wordlist_last);
static int	take_redirect(t_minishell *shell, t_redirect ***redirect_last);
static int	take_redirect_internal(t_minishell *shell, t_redirect **redirect);
static int	add_herdoc(t_minishell *shell, t_document *document);

int	take_element(t_minishell *shell, t_element *element)
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
		if (shell->token.type == TK_WORD)
			ret = take_word(shell, &wordlist_last);
		else if (is_redirect_token(shell->token.type))
			ret = take_redirect(shell, &redirect_last);
		else
			break ;
	}
	if (ret == FATAL_ERR || ret == INTERRUPT)
	{
		dispose_wordlist(element->wordlist);
		dispose_redirect(element->redirect);
		ft_bzero(&element, sizeof(*element));
	}
	return (ret);
}

static int	take_word(t_minishell *shell, t_wordlist ***wordlist_last)
{
	char		*word;
	t_wordlist	*wordlist;

	word = ft_substr(&shell->string[shell->token.start], 0, shell->token.len);
	if (!word)
		return (FATAL_ERR);
	wordlist = malloc(sizeof(t_wordlist));
	if (!wordlist)
	{
		free(word);
		return (FATAL_ERR);
	}
	wordlist->next = NULL;
	wordlist->word = word;
	**wordlist_last = wordlist;
	*wordlist_last = &wordlist->next;
	return (lexer(shell));
}

static int	take_redirect(t_minishell *shell, t_redirect ***redirect_last)
{
	int			ret;
	t_redirect	*redirect;

	ret = take_redirect_internal(shell, &redirect);
	if (ret)
		return (ret);
	**redirect_last = redirect;
	*redirect_last = &redirect->next;
	if (redirect->type == RT_HEREDOC)
		ret = add_herdoc(shell, redirect->value.document);
	if (ret)
		return (ret);
	return (lexer(shell));
}

static int	take_redirect_internal(t_minishell *shell, t_redirect **redirect)
{
	int			ret;
	char		*word;
	t_redirtype	type;

	type = shell->token.type - TK_INPUT;
	ret = lexer(shell);
	if (ret)
		return (ret);
	if (shell->token.type != TK_WORD)
		return (SYNTAX_ERR);
	word = ft_substr(&shell->string[shell->token.start], 0, shell->token.len);
	if (!word)
		return (FATAL_ERR);
	*redirect = make_redirect(type, word);
	if (!redirect)
	{
		free(word);
		return (FATAL_ERR);
	}
	return (NOERR);
}

static int	add_herdoc(t_minishell *shell, t_document *document)
{
	t_heredoc	**temp;
	t_heredoc	*heredoc;

	heredoc = malloc(sizeof(t_heredoc));
	if (!heredoc)
		return (FATAL_ERR);
	heredoc->document = document;
	heredoc->next = NULL;
	temp = &shell->heredoc;
	while (*temp)
		temp = &(*temp)->next;
	*temp = heredoc;
	return (NOERR);
}
