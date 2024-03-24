/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_wordlist_split.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 01:20:02 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 12:58:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "subst.h"
#include <libft.h>
#include <stdlib.h>

static int	wordlist_split_internal(char *string, t_wordlist **wordlist_last);
static int	next_word(char *string, size_t *start, size_t *index);

int	wordlist_split(char *string, t_wordlist **result)
{
	int	ret;

	*result = NULL;
	ret = wordlist_split_internal(string, result);
	if (ret)
		dispose_wordlist(*result);
	return (ret);
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
			return (FATAL_ERR);
		*wordlist_last = malloc(sizeof(t_wordlist));
		if (!*wordlist_last)
		{
			free(word);
			return (FATAL_ERR);
		}
		(*wordlist_last)->word = word;
		(*wordlist_last)->next = NULL;
		wordlist_last = &(*wordlist_last)->next;
	}
	return (NOERR);
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
