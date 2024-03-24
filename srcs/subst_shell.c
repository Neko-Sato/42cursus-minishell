/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 00:45:31 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 12:58:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "subst.h"
#include <libft.h>
#include <stdlib.h>

int	shell_expand_wordlist(t_minishell *shell, t_wordlist *wordlist,
		t_wordlist **result)
{
	int			ret;
	t_wordlist	**result_last;
	t_wordlist	*temp;

	ret = NOERR;
	*result = NULL;
	result_last = result;
	while (wordlist)
	{
		ret = shell_expand_word(shell, wordlist->word, &temp);
		if (ret)
		{
			dispose_wordlist(*result);
			return (ret);
		}
		*result_last = temp;
		while (temp && temp->next)
			temp = temp->next;
		if (temp)
			result_last = &temp->next;
		wordlist = wordlist->next;
	}
	return (ret);
}

int	shell_expand_word(t_minishell *shell, char *string, t_wordlist **result)
{
	int		ret;
	char	*temp;

	temp = shell_expand_string(shell, string, 0);
	if (!temp)
		return (FATAL_ERR);
	ret = wordlist_split(temp, result);
	free(temp);
	return (ret);
}

static int	shell_expand_string_internal(t_minishell *shell, t_strgen *strgen,
		char *string, int heredoc);

char	*shell_expand_string(t_minishell *shell, char *string, int heredoc)
{
	t_strgen	*strgen;
	char		*temp;

	strgen = ft_strgennew(STRGEN_BUUFERSIZE);
	if (!strgen)
		return (NULL);
	if (shell_expand_string_internal(shell, strgen, string, heredoc))
		temp = NULL;
	else
		temp = ft_strgencomp(strgen);
	ft_strgendel(strgen);
	return (temp);
}

static int	shell_expand_string_internal(t_minishell *shell, t_strgen *strgen,
		char *string, int heredoc)
{
	int		ret;
	int		c;
	size_t	sindex;

	ret = NOERR;
	sindex = 0;
	while (!ret)
	{
		c = string[sindex++];
		if (!c)
			break ;
		if (c == '\1' && !heredoc)
			ret = ft_strgenstr(strgen, "\1\1");
		else if (c == '\'' && !heredoc)
			ret = case_singlequote(shell, strgen, string, &sindex);
		else if (c == '"' && !heredoc)
			ret = case_doublequote(shell, strgen, string, &sindex);
		else if (c == '~' && !heredoc)
			ret = case_tilde(shell, strgen, string, &sindex);
		else if (c == '$')
			ret = case_dollar(shell, strgen, string, &sindex);
		else
			ret = ft_strgenchr(strgen, string[sindex - 1]);
	}
	return (ret);
}
