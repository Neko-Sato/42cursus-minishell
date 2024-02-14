/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:19:13 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/14 21:16:11 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <libft.h>
#include <stddef.h>

/*
	シングルクォート展開
	doubleクォート展開
	環境変数展開 (クォートの中でなければリストを分ける)
	最後にリスト全て、アスタリスクの展開をする
*/
int	case_variable(t_wordlist **word, size_t *pos, char *variable[]);

int	wordlist_expend(t_wordlist *word, char *variable[])
{
	int	ret;

	ret = wordlist_expend(word, variable);
	if (ret)
		return (ret);
	ret = wordlist_wildcard_expend(word);
	return (ret);
}

int	wordlist_expend(t_wordlist *word)
{
	size_t	pos;
	int		c;

	pos = 0;
	while (1)
	{
		c = word->word[pos];
		if (!c)
			break ;
		i++;
		if (c == '"')
			;
		else if (c == '\'')
			;
		else if (c == '$')
			;
	}
	//アスタリスクの展開
}

int	case_variable(t_wordlist **word, size_t *pos, char *variable[])
{
	int c;
	size_t start;
	char *temp;

	start = *pos;
	while (1)
	{
		c = (*word)->word[*pos];
		if (c == '\0' || c == '"' || c == '\'' || c == '*')
			break ;
		*pos++;
	}
	temp = ft_substr(&(*word)->word[start], 0, *pos - start);
	if (!temp)
		return (-1);

	free(temp);
	return (0);
}