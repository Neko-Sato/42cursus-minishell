/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordlist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:58:31 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 12:58:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "command.h"
#include <stdlib.h>

char	**wordlist2strarray(t_wordlist *wordlist)
{
	char		**result;
	size_t		i;
	t_wordlist	*temp;

	i = 0;
	temp = wordlist;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	temp = wordlist;
	while (temp)
	{
		result[i++] = temp->word;
		temp = temp->next;
	}
	result[i] = NULL;
	return (result);
}

int	strarray2wordlist(char **array, t_wordlist **result)
{
	t_wordlist	**result_last;
	t_wordlist	*temp;

	result_last = result;
	while (*array)
	{
		temp = malloc(sizeof(t_wordlist));
		if (!temp)
		{
			while (*result)
			{
				temp = *result;
				*result = (*result)->next;
				free(temp);
			}
			return (FATAL_ERR);
		}
		temp->next = NULL;
		temp->word = *array++;
		*result_last = temp;
		result_last = &temp->next;
	}
	return (NOERR);
}
