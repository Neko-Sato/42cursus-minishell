/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 21:34:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/24 23:46:44 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>

/*
	- 文字列を生成する関数
	- 文字列からwordlistに分割する関数
	- デクォートする関数
*/

int	shell_expend_wordlist(t_minishell *shell, char *string, t_wordlist **result)
{
	char	*temp;

	temp = ___(); //文字列を生成する
	if (!temp)
		return (SYSTEM_ERR);
	if (split_wordlist(temp, result)) //空白文字で分割する、'\1'でエスケープされている
		return (SYSTEM_ERR);
	return (NOERR);
}

int	shell_expend_word(t_minishell *shell, char *string, t_strgen *strgen,
		int heredoc)
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
			ret = case_singlequote(strgen, string, &sindex);
		else if (c == '"' && !heredoc)
			ret = case_doublequote(shell, strgen, string, &sindex);
		else if (c == '~' && !heredoc)
			ret = case_tilde(shell, strgen, string, &sindex);
		else if (c == '$')
			ret = case_variable(shell, strgen, string, &sindex);
		else
			ret = ft_strgenchr(strgen, string[sindex - 1]);
	}
	return (ret);
}

int	case_singlequote(t_strgen *strgen, char *string, size_t *sindex)
{
	int	c;

	while (1)
	{
		c = string[*sindex];
		if (!c)
			break ;
		(*sindex)++;
		if (c == '\'')
			break ;
		if (ft_strgenstr(strgen, (char[]){'\1', c, '\0'}))
			return (SYSTEM_ERR);
	}
	return (NOERR);
}

int	case_doublequote(t_minishell *shell, t_strgen *strgen, char *string,
		size_t *sindex)
{
	char	*temp;
	int		c;

	while (1)
	{
		c = string[*sindex];
		if (!c)
			break ;
		(*sindex)++;
		if (c == '"')
			break ;
		if (c == '$')
		{
			temp = param_expand(shell, string, sindex);
			ret = ;
			free(temp);
			if (ret)
				return (ret);
		}
		else if (ft_strgenstr(strgen, (char[]){'\1', c, '\0'}))
			return (SYSTEM_ERR);
	}
	return (NOERR);
}

static int	quote何とか(t_strgen *strgen, char *string)
{
	size_t	pos;
	int		c;

	while (1)
	{
		c = string[pos++];
		if (!c)
			break ;
		if (ft_strgenstr(strgen, (char[]){'\1', c, '\0'}))
			return (SYSTEM_ERR);
	}
	return (NOERR);
}

int	case_singlequote(t_minishell *shell, t_strgen *strgen, char *string,
		size_t *sindex)
{
	int	c;

	while (1)
	{
		c = string[(*sindex)++];
		if (ft_strchr("'", c))
			break ;
		if (ft_strgenstr(strgen, (char[]){'\1', c, '\0'}))
			;
	}
}

int	case_variable(t_minishell *shell, t_strgen *strgen, char *string,
		size_t *sindex)
{
	char *temp;
	int c;

	size_t
		temp = param_expand(shell, string, sindex);
	if (!temp)
		return (SYSTEM_ERR);
	if (ft_strgenstr(strgen, temp))
		return (SYSTEM_ERR);
	free(temp);
	return (NOERR);
}