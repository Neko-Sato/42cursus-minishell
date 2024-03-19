/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_glob.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 21:34:52 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 20:55:23 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "glob.h"
#include "shell.h"
#include "subst.h"
#include <libft.h>
#include <stdlib.h>

int	glob_expand_wordlist(t_minishell *shell,
		t_wordlist *wordlist, t_wordlist **result)
{
	int			ret;
	t_wordlist	**result_last;
	t_wordlist	*temp;

	ret = 0;
	*result = NULL;
	result_last = result;
	while (wordlist)
	{
		ret = glob_expand_word(shell, wordlist->word, &temp);
		if (ret)
		{
			dispose_wordlist(*result);
			return (ret);
		}
		*result_last = temp;
		while (temp->next)
			temp = temp->next;
		result_last = &temp->next;
		wordlist = wordlist->next;
	}
	return (ret);
}

static char	**glob_expand_word_internal(char *string);

int	glob_expand_word(t_minishell *shell, char *string, t_wordlist **result)
{
	int			ret;
	char		**arry;

	(void)shell;
	arry = glob_expand_word_internal(string);
	if (!arry)
		return (-1);
	ft_sortstrarry(arry);
	ret = strarray2wordlist(arry, result);
	if (ret)
		ft_2darraydel(arry);
	else
		free(arry);
	return (ret);
}

static char	**glob_expand_word_internal(char *string)
{
	char	**arry;
	char	*temp;

	if (unquoted_glob_pattern(string))
	{
		temp = quote_string_for_globbing(string);
		arry = globfilename(temp);
		free(temp);
		if (!arry)
			return (NULL);
		if (arry[0])
			return (arry);
		ft_2darraydel(arry);
	}
	temp = dequote_string(string);
	if (!temp)
		return (NULL);
	arry = malloc(sizeof(char *[2]));
	if (!arry)
		free(temp);
	arry[0] = temp;
	arry[1] = NULL;
	return (arry);
}

int	unquoted_glob_pattern(char *string)
{
	while (*string)
	{
		if (*string == '\1')
			if (*++string)
				break ;
		if (*string++ == '*')
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
		if (ft_strgenchr(strgen, *string++))
			ret = -1;
	}
	result = NULL;
	if (!ret)
		result = ft_strgencomp(strgen);
	ft_strgendel(strgen);
	return (result);
}
