/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:19:13 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 20:29:12 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "subst.h"

int	expand_wordlist(t_minishell *shell,
		t_wordlist *wordlist, t_wordlist **result)
{
	int			ret;
	t_wordlist	*temp;

	ret = shell_expand_wordlist(shell, wordlist, &temp);
	if (ret)
		return (ret);
	ret = glob_expand_wordlist(shell, temp, result);
	dispose_wordlist(temp);
	return (ret);
}

char	*string_quote_removal(char *string)
{
	int			ret;
	char		*result;
	t_strgen	*strgen;

	ret = 0;
	strgen = ft_strgennew(STRGEN_BUUFERSIZE);
	if (!strgen)
		return (NULL);
	while (!ret && *string)
	{
		if (ft_strnchr("'\"", *string, 2))
			;
		else if (ft_strgenchr(strgen, *string))
			ret = -1;
		string++;
	}
	result = NULL;
	if (!ret)
		result = ft_strgencomp(strgen);
	ft_strgendel(strgen);
	return (result);
}
