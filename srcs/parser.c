/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 03:19:56 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/02 14:26:26 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include <libft.h>
#include <stddef.h>

int	___(t_minishell *gvars, char **line, size_t *pos)
{
	int		ret;
	char	*word;
	t_token	token;
	t_xlst	*word_list;

	word_list = NULL;
	while ((*line)[*pos])
	{
		ret = get_word(line, pos, &word);
		if (ret || (word && ft_xlstappend(&word_list, &word, sizeof(char *))))
			return (-1);
		token = get_token(line, pos);
		if (token)
		{

		}
	}
	return (0);
}
