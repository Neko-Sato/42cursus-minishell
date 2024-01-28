/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:03:07 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/27 09:22:21 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "minishell.h"
# include "word.h"

typedef enum e_redirecttype
{
	r_redirect,
	r_here_doc,
	r_append,
	r_overwrite,
}						t_redirecttype;

typedef struct s_redirect
{
	struct s_redirect	*next;
	t_redirecttype		type;
	char				*filename;
}						t_redirect;

typedef enum e_commandtype
{
	c_simple,
	c_conncom,
}						t_commandtype;

typedef struct s_simplecom
{
	t_redirect			*redirect;
	t_wordlist			*wordlist;
}						t_simplecom;

typedef enum e_concomtype
{
	cc_and,
	cc_or,
	cc_pipe,
	cc_end,
}						t_concomtype;

typedef struct s_conncom
{
	t_concomtype		concomtype;
	struct s_command	*command1;
	struct s_command	*command2;
}						t_conncom;

typedef struct s_command
{
	t_commandtype		type;
	union
	{
		t_simplecom		*simplecom;
		t_conncom		*conncom;
	} value;
}						t_command;

int						reader_command(t_minishell *gvars);

#endif