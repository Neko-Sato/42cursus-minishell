/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:58:17 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/25 15:39:53 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>

# define PS1 "minishell> "
# define PS2 "> "

typedef struct s_minishell
{
	char		**envp;
	char		**vars;
	int			isinteractive;
	int			last_status;
	char		*line;
	size_t		pos;
	t_command	*cmd;
}				t_minishell;

int				minishell_init(t_minishell *args, char *envp[]);
void			minishell_destroy(t_minishell *args);

int				repl(t_minishell *args);

#endif