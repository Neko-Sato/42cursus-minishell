/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 02:55:01 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/10 12:40:02 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "word.h"

typedef enum s_redirecttype
{
	RT_INPUT,
	RT_HEREDOC,
	RT_OVERWRITE,
	RT_APPEND,
}							t_redirecttype;

typedef struct s_redirect
{
	struct s_redirect		*next;
	t_redirecttype			type;
	char					*word;
}							t_redirect;

typedef struct s_command	t_command;

typedef enum s_commandtype
{
	CT_NONE,
	CT_SIMPLE,
	CT_CONNCOM,
	CT_GROUP,
}							t_commandtype;

typedef struct s_simplecom
{
	t_redirect				*redirect;
	t_wordlist				*wordlist;
}							t_simplecom;

typedef enum e_concomtype
{
	CCT_PIPE,
	CCT_AND,
	CCT_OR,
}							t_concomtype;

typedef struct s_conncom
{
	t_concomtype			type;
	t_command				*command1;
	t_command				*command2;
}							t_conncom;

typedef struct s_groupcom
{
	t_command				*command;
}							t_groupcom;

typedef struct s_command
{
	t_commandtype			type;
	union
	{
		t_simplecom			*simplecom;
		t_conncom			*conncom;
		t_groupcom			*groupcom;
	} value;
}							t_command;

void						command_dispose(t_command *command);

t_command					*make_simplecom(t_wordlist *wordlist,
								t_redirect *redirect);
t_command					*make_conncom(t_concomtype type,
								t_command *command1, t_command *command2);
t_command					*make_groupcom(t_command *command);

#endif