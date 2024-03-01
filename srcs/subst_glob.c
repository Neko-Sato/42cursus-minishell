/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_glob.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 21:34:52 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/01 18:27:06 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "shell.h"
#include "subst.h"
#include <libft.h>
#include <stdlib.h>

t_wordlist	*glob_expand_wordlist(t_minishell *shell, t_wordlist *wordlist)
{
	t_wordlist	*result;
	t_wordlist	**result_last;
	t_wordlist	*temp;

	result = NULL;
	result_last = &result;
	while (wordlist)
	{
		temp = glob_expand_word(shell, wordlist->word);
		if (!temp)
		{
			dispose_wordlist(result);
			return (NULL);
		}
		*result_last = temp;
		while (temp->next)
			temp = temp->next;
		result_last = &temp->next;
		wordlist = wordlist->next;
	}
	return (result);
}

/*
	ガチャガチャする
*/
t_wordlist	*glob_expand_word(t_minishell *shell, char *string)
{
	char		*temp;
	char		*arry;
	t_wordlist	*result;

	if (unquoted_glob_pattern(string))
	{
		temp = quote_string_for_globbing(string);
		if (!temp)
			return (NULL);
		arry = globfilename(temp);
		free(temp);
	}
	else
	{
		arry = dequote_string(string);
	}
	result = strarry2wordlist(arry);
	if (result)
		free(arry);
	else
		ft_2darraydel(arry);
	return (result);
}

/*
	ガチャガチャする
*/
t_wordlist	*strarry2wordlist(char **arry)
{
	t_wordlist	*temp;
	t_wordlist	*result;
	t_wordlist	**result_last;

	while (*arry)
	{
		temp = malloc(sizeof(t_wordlist *));
		if (!temp)
		{
			dispose_wordlist(result);
			return (NULL);
		}
	}
	return (result);
}

int	unquoted_glob_pattern(char *string)
{
	while (*string)
	{
		if (*string == '\1')
			if (*++string)
				break ;
		if (*string == '*')
			return (1);
	}
	return (0);
}

char	*quote_string_for_globbing(char *string)
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
		if (*string == '\1')
		{
			if (*++string)
				break ;
			if (ft_strnchr("\\*", *string, 2) && ft_strgenchr(strgen, '\\'))
				ret = -1;
		}
		if (ft_strgenchr(strgen, *string))
			ret = -1;
	}
	result = NULL;
	if (ret)
		result = ft_strgencomp(strgen);
	ft_strgendel(strgen);
	return (result);
}
