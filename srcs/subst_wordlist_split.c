/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_wordlist_split.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 01:20:02 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/27 02:09:30 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "subst.h"
#include <libft.h>
#include <stdlib.h>

static int	wordlist_split_internal(char *string, t_wordlist **wordlist_last);
static int	next_word(char *string, size_t *start, size_t *index);

t_wordlist	*wordlist_split(char *string)
{
	t_wordlist	*wordlist;

	wordlist = NULL;
	if (wordlist_split_internal(string, &wordlist))
	{
		dispose_wordlist(wordlist);
		return (NULL);
	}
	return (wordlist);
}

static int	wordlist_split_internal(char *string, t_wordlist **wordlist_last)
{
	char	*word;
	size_t	start;
	size_t	index;

	index = 0;
	while (string[index])
	{
		if (next_word(string, &start, &index))
			break ;
		word = ft_substr(&string[start], 0, index - start);
		if (!word)
			return (-1);
		*wordlist_last = malloc(sizeof(t_wordlist));
		if (!*wordlist_last)
		{
			free(word);
			return (-1);
		}
		(*wordlist_last)->word = word;
		(*wordlist_last)->next = NULL;
		wordlist_last = &(*wordlist_last)->next;
	}
	return (0);
}

static int	next_word(char *string, size_t *start, size_t *index)
{
	while (ft_isblank(string[*index]))
		(*index)++;
	if (!string[*index])
		return (1);
	*start = *index;
	while (string[*index] && !ft_isblank(string[*index]))
	{
		if (string[*index] == '\1')
		{
			if (!string[++*index])
				break ;
		}
		(*index)++;
	}
	return (0);
}
