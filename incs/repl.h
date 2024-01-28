/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:58:17 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/28 21:39:56 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPL_H
# define REPL_H

# include "command.h"
# include "minishell.h"
# include <stddef.h>

extern int				interruption;

typedef struct s_heredoc
{
	struct s_heredoc	*next;
	char				*eof;
	char				*contents;
}						t_heredoc;

typedef struct s_repl
{
	size_t				lineno;
	char				*line;
	size_t				pos;
	t_heredoc			heredoc;
	int					status_code;
}						t_repl;

int						reader_loop(t_minishell *gvars);
int						put_prompt(t_minishell *gvars, t_repl *vars);

#endif