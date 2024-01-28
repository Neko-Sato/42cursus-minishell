/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 00:00:08 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/26 22:02:06 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

#include <libft.h>

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
	t_list				*wordlist;
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
	t_redirect			*redirect;
	union
	{
		t_simplecom		simplecom;
		t_conncom		conncom;
	} value;
}						t_command;

typedef struct s_minishell
{
	char				**envp;
	char				**vars;
	int					isttay;
	t_command			*command;
	t_list				*herdoc_tag;
}						t_minishell;


int	put_prompt(t_minishell *vars);

reader_loop(vars)
{
	while (1)
	{
	}
}

int	lexer(t_minishell *vars)
{
	t_strgen	*strgen;
	t_command	*command;

	strgen = ft_strgennew();
	command = malloc(sizeof(t_command));
	command->redirect = NULL;
	command->type = c_simple;
	command->value.simplecom.redirect = NULL;
	command->value.simplecom.wordlist = NULL;
	put_prompt(vars);
	while (1)
	{		
		if (ft_isblank(vars->line[vars->pos]))
			;//区切り文字、出てきたら区切り文字が終わるまで繰り返す
		ft_strgenchr(strgen, vars->line[vars->pos]);
		vars->pos++;
	}
	vars->line[vars];
	free()
}

int	read_command(t_minishell *vars)
{
	free(vars->line);
	vars->line = NULL;
	vars->pos = 0;
	lexer(vars);
	read_heredoc(vars);
	add_history(vars->line);
	return (0);
}

int	read_heredoc(t_minishell *vars)
{
}

/*
lineがNULLならprimarypromptでreadline
値があればセカンダリーpromptでreadlineしjoinする
*/
int	put_prompt(t_minishell *vars)
{
	char	*temp;
	char	*next;

	if (!vars->line)
		vars->line = readline(PS1);
	else
	{
		temp = vars->line;
		next = readline(PS2);
		if (next)
			vars->line = ft_strjoin(temp, next);//strjooinじゃなくて次の行に追加する
		else
			vars->line = NULL;
		free(temp);
		free(next);
	}
	if (!vars->line)
		return (-1);
	return (0);
}
