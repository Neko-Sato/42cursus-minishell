/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 21:32:18 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/25 00:04:46 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBST_H
# define SUBST_H

# include "command.h"

int		shell_expend_wordlist(t_wordlist *wordlist, t_wordlist **result,
			char *variable[]);
int		glob_expend_wordlist(t_wordlist *wordlist, t_wordlist **result,
			char *variable[]);

char	*quote_string(char *string);
char	*dequote_string(char *string);

char	*string_extract_double_quoted(t_minishell *shell, char *string,
			size_t *sindex);
char	*string_extract_single_quoted(t_minishell *shell, char *string,
			size_t *sindex);
char	*param_expand(t_minishell *shell, char *string, size_t *sindex);

#endif
