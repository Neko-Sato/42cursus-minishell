/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:19:13 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/01 18:21:51 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "subst.h"

t_wordlist	*expand_wordlist(t_minishell *shell, t_wordlist *wordlist)
{
	t_wordlist	*result;
	t_wordlist	*temp;

	temp = shell_expand_wordlist(shell, wordlist);
	if (!temp)
		return (NULL);
	result = glob_expand_wordlist(shell, temp);
	dispose_wordlist(temp);
	return (result);
}
