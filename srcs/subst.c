/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:19:13 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/25 18:52:58 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "subst.h"

int	expand_wordlist(t_minishell *shell,
					t_wordlist *wordlist,
					t_wordlist **result)
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

	ret = NOERR;
	strgen = ft_strgennew(STRGEN_BUUFERSIZE);
	if (!strgen)
		return (NULL);
	while (!ret && *string)
	{
		if (ft_strnchr("'\"", *string, 2))
			;
		else if (ft_strgenchr(strgen, *string))
			ret = FATAL_ERR;
		string++;
	}
	result = NULL;
	if (!ret)
		result = ft_strgencomp(strgen);
	ft_strgendel(strgen);
	return (result);
}

static int	ansic_quote_internal(t_strgen *strgen, char *str);

char	*ansic_quote(char *str)
{
	char		*result;
	t_strgen	*strgen;

	strgen = ft_strgennew(STRGEN_BUUFERSIZE);
	result = NULL;
	if (!ansic_quote_internal(strgen, str))
		result = ft_strgencomp(strgen);
	ft_strgendel(strgen);
	return (result);
}

static int	ansic_quote_internal(t_strgen *strgen, char *str)
{
	int	ret;

	ret = 0;
	if (!*str)
		ret = ft_strgenstr(strgen, "''");
	while (!ret && *str)
	{
		if (*str == '\'')
		{
			ret = ft_strgenchr(strgen, '"');
			while (!ret && *str++ == '\'')
				ret = ft_strgenchr(strgen, '\'');
			ret = ret || ft_strgenchr(strgen, '"');
		}
		if (ret || !*str)
			break ;
		ret = ft_strgenchr(strgen, '\'');
		while (!ret && *str && *str != '\'')
			ret = ft_strgenchr(strgen, *str++);
		ret = ret || ft_strgenchr(strgen, '\'');
	}
	if (ret)
		return (FATAL_ERR);
	return (NOERR);
}
