/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:35:37 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/22 23:44:31 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLE_H
# define VARIABLE_H

# define V_EXPORTED 0b01
# define ASS_APPEND 0b01

typedef struct s_var
{
	char					*key;
	char					*value;
	int						attr;
}							t_var;

typedef struct s_minishell	t_minishell;

char						**get_envp(t_minishell *shell);
t_var						*find_variable(t_minishell *shell, char *key);
char						*get_string_value(t_minishell *shell, char *key);

t_var						*bind_variable(t_minishell *shell, char *key,
								char *value, int flag);
void						unbind_variable(t_minishell *shell, char *key);

t_var						*make_new_variable(char *key);
void						dispose_variable(t_var *var);

int							legal_identifier(char *name);
int							do_assignment(t_minishell *shell, char *word);

int							set_var_attribute(t_minishell *shell, char *name,
								int attr, int undo);

#endif