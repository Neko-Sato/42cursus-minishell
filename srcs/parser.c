/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:34:56 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/11 03:13:22 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "parser.h"
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

int	parser(t_lexical *lexical, t_command **command, t_heredoc **heredoc)
{
	int			ret;
	t_parser	parser;

	*heredoc = NULL;
	parser.lexical = lexical;
	parser.heredoc = heredoc;
	parser.brackets_level = 0;
	ret = take_command(&parser, command);
	if (ret == 1)
		ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
	if (ret)
	{
		dispose_heredoc(*heredoc);
		*heredoc = NULL;
	}
	return (ret);
}

void	dispose_heredoc(t_heredoc *heredoc)
{
	void	*temp;

	while (heredoc)
	{
		free(heredoc->contents);
		temp = heredoc;
		heredoc = heredoc->next;
		free(temp);
	}
}
