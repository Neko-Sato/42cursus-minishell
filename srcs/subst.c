/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:19:13 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/24 13:20:36 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "subst.h"
#include <libft.h>
#include <stddef.h>

/*
	クォート展開とparam展開の二種あってフラグでどちらをするか示せるように
*/

int	expend_wordlist(t_minishell *shell, t_wordlist *wordlist, t_wordlist **result)
{
	int			ret;
	t_wordlist	*new_wordlist;

	*result = NULL;
	new_wordlist = NULL;
	ret = shell_expend_wordlist(&wordlist, &new_wordlist, variable);
	if (ret)
		return (ret);
	wordlist = new_wordlist;
	new_wordlist = NULL;
	ret = glob_expend_wordlist(&wordlist, new_wordlist, variable);
	dispose_wordlist(wordlist);
	*result = new_wordlist;
	return (ret);
}

int	shell_expend_wordlist(t_wordlist *wordlist, t_wordlist **result,
		char *variable[])
{
	int			ret;
	t_wordlist	**result_last;
	t_wordlist	*expand;

	*result = NULL;
	result_last = result;
	while (wordlist)
	{
		ret = shell_expend_word(wordlist->word, &expand, variable);
		if (ret)
			break ;
		*result_last = expand;
		while (expand->next)
			expand = expand->next;
		result_last = &expand->next;
		wordlist = wordlist->next;
	}
	if (ret)
	{
		dispose_wordlist(*result);
		*result = NULL;
	}
	return (ret);
}

int	glob_expend_wordlist(t_wordlist *wordlist, t_wordlist **result,
		char *variable[])
{
	int			ret;
	t_wordlist	**result_last;
	t_wordlist	*expand;

	*result = NULL;
	result_last = result;
	while (wordlist)
	{
		ret = glob_expend_word(wordlist->word, &expand, variable);
		if (ret)
			break ;
		*result_last = expand;
		while (expand->next)
			expand = expand->next;
		result_last = &expand->next;
		wordlist = wordlist->next;
	}
	if (ret)
	{
		dispose_wordlist(*result);
		*result = NULL;
	}
	return (ret);
}
