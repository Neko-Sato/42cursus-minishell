/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 21:32:18 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/23 02:08:03 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBST_H
# define SUBST_H

# include "command.h"
# include <libft.h>

int		expand_wordlist(t_minishell *shell,
			t_wordlist *wordlist, t_wordlist **result);
int		shell_expand_word(t_minishell *shell,
			char *string, t_wordlist **result);
int		shell_expand_wordlist(t_minishell *shell,
			t_wordlist *wordlist, t_wordlist **result);
int		glob_expand_word(t_minishell *shell,
			char *string, t_wordlist **result);
int		glob_expand_wordlist(t_minishell *shell,
			t_wordlist *wordlist, t_wordlist **result);

char	*shell_expand_string(t_minishell *shell,
			char *string, int heredoc);
char	*string_extract_single_quoted(t_minishell *shell,
			char *string, size_t *sindex);
char	*string_extract_double_quoted(t_minishell *shell,
			char *string, size_t *sindex);
char	*param_expand(t_minishell *shell, char *string, size_t *sindex);

int		case_singlequote(t_minishell *shell, t_strgen *strgen,
			char *string, size_t *sindex);
int		case_doublequote(t_minishell *shell, t_strgen *strgen,
			char *string, size_t *sindex);
int		case_tilde(t_minishell *shell, t_strgen *strgen,
			char *string, size_t *sindex);
int		case_dollar(t_minishell *shell, t_strgen *strgen,
			char *string, size_t *sindex);

char	*quote_string(char *string);
char	*dequote_string(char *string);
int		wordlist_split(char *string, t_wordlist **result);

int		unquoted_glob_pattern(char *string);
char	*quote_string_for_globbing(char *string);

char	*string_quote_removal(char *string);

char	*ansic_quote(char *str);

#endif
