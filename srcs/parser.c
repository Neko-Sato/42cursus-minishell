/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:34:56 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/14 18:42:12 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "parser.h"
#include "shell.h"
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

static int	read_heredoc(t_heredoc *heredoc, int interactive);
static char	*strjoin_at_newline(char *line, char *new_line);

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

int	gather_heredoc(t_heredoc *heredoc, int interactive)
{
	int			ret;
	t_heredoc	*next;

	ret = 0;
	next = heredoc;
	while (next)
	{
		ret = read_heredoc(next, interactive);
		if (ret)
			break ;
		next = next->next;
	}
	if (ret == 1)
		ft_putstr_fd("minishell: here-document error\n", STDERR_FILENO);
	return (ret);
}

static int	read_heredoc(t_heredoc *heredoc, int interactive)
{
	char	*temp;
	char	*line;

	heredoc->contents = NULL;
	while (1)
	{
		line = minishell_readline(PS2, interactive);
		if (g_interrupt_state)
			return (2);
		if (!line)
			return (1);
		if (!ft_strcmp(line, heredoc->eof))
			break ;
		temp = strjoin_at_newline(heredoc->contents, line);
		free(line);
		if (!temp)
			return (-1);
		free(heredoc->contents);
		heredoc->contents = temp;
	}
	return (0);
}

static char	*strjoin_at_newline(char *line, char *new_line)
{
	char	*ret;
	size_t	size;

	if (!line)
		return (ft_strdup(new_line));
	if (!new_line)
		return (ft_strdup(line));
	size = ft_strlen(line) + ft_strlen(new_line) + 2;
	ret = (char *)malloc(sizeof(char) * size);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, line, size);
	ft_strlcat(ret, "\n", size);
	ft_strlcat(ret, new_line, size);
	return (ret);
}
