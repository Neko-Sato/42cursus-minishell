/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 02:55:01 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/11 03:26:43 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "element.h"

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

typedef union u_comvalue
{
	t_simplecom				*simplecom;
	t_conncom				*conncom;
	t_groupcom				*groupcom;
}							t_comvalue;

typedef struct s_command
{
	t_commandtype			type;
	t_comvalue				value;
}							t_command;

void						dispose_command(t_command *command);

t_command					*make_simplecom(t_wordlist *wordlist,
								t_redirect *redirect);
t_command					*make_conncom(t_concomtype type,
								t_command *command1, t_command *command2);
t_command					*make_groupcom(t_command *command);

#endif