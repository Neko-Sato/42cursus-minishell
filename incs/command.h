/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 02:55:01 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/07 17:45:52 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_wordlist
{
	struct s_wordlist		*next;
	char					*word;
}							t_wordlist;

typedef enum s_redirtype
{
	RT_INPUT,
	RT_HEREDOC,
	RT_OVERWRITE,
	RT_APPEND,
}							t_redirtype;

typedef struct s_document
{
	char					*eof;
	int						quoted;
	char					*document;
}							t_document;

typedef union s_redirvalue
{
	char					*filename;
	t_document				*document;
}							t_redirvalue;

typedef struct s_redirect
{
	struct s_redirect		*next;
	t_redirtype				type;
	t_redirvalue			value;
}							t_redirect;

typedef struct s_heredoc
{
	struct s_heredoc		*next;
	t_document				*document;
}							t_heredoc;

typedef struct s_element
{
	t_redirect				*redirect;
	t_wordlist				*wordlist;
}							t_element;

typedef struct s_command	t_command;

typedef enum s_commandtype
{
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

typedef struct s_minishell	t_minishell;

int							read_command(t_minishell *shell);
int							parse_command(t_minishell *shell);

void						dispose_command(t_command *command);
void						dispose_wordlist(t_wordlist *wordlist);
void						dispose_redirect(t_redirect *redirect);
void						dispose_heredoc(t_heredoc *heredoc);

t_command					*make_simplecom(t_element *element);
t_command					*make_conncom(t_concomtype type,
								t_command *command1, t_command *command2);
t_command					*make_groupcom(t_command *command);
t_redirect					*make_redirect(t_redirtype type, char *filename);

char						**wordlist2strarray(t_wordlist *wordlist);
t_wordlist					*strarray2wordlist(char **array);

int							execute_command(t_minishell *shell,
								t_command *command);

#endif
