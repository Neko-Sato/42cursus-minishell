/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 23:01:14 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 12:58:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "subst.h"
#include <libft.h>
#include <stdlib.h>

char	*quote_string(char *string)
{
	char	*head;
	char	*temp;

	if (!string)
		return (NULL);
	temp = malloc(ft_strlen(string) * 2 + 1);
	if (!temp)
		return (NULL);
	head = temp;
	while (*string)
	{
		*temp++ = '\1';
		*temp++ = *string++;
	}
	*temp = '\0';
	return (head);
}

char	*dequote_string(char *string)
{
	t_strgen	*strgen;
	char		*head;

	strgen = ft_strgennew(STRGEN_BUUFERSIZE);
	if (!strgen)
		return (NULL);
	while (*string)
	{
		if (*string == '\1')
		{
			if (!*++string)
				break ;
		}
		if (ft_strgenchr(strgen, *string++))
		{
			ft_strgendel(strgen);
			return (NULL);
		}
	}
	head = ft_strgencomp(strgen);
	ft_strgendel(strgen);
	return (head);
}

char	*string_extract_single_quoted(t_minishell *shell, char *string,
		size_t *sindex)
{
	char	*temp;
	int		c;
	size_t	zindex;

	(void)shell;
	zindex = *sindex;
	while (1)
	{
		c = string[zindex];
		if (!c || c == '\'')
			break ;
		zindex++;
	}
	temp = ft_substr(&string[*sindex], 0, zindex - *sindex);
	if (!temp)
		return (NULL);
	if (c)
		zindex++;
	*sindex = zindex;
	return (temp);
}

static int	string_extract_double_quoted_internal(
			t_minishell *shell, t_strgen *strgen, char *string, size_t *sindex);

char	*string_extract_double_quoted(t_minishell *shell, char *string,
		size_t *sindex)
{
	int			ret;
	t_strgen	*strgen;
	char		*temp;
	size_t		zindex;

	strgen = ft_strgennew(STRGEN_BUUFERSIZE);
	if (!strgen)
		return (NULL);
	zindex = *sindex;
	ret = string_extract_double_quoted_internal(shell, strgen, string, &zindex);
	if (ret)
		temp = NULL;
	else
		temp = ft_strgencomp(strgen);
	ft_strgendel(strgen);
	*sindex = zindex;
	return (temp);
}

static int	string_extract_double_quoted_internal(
	t_minishell *shell, t_strgen *strgen, char *string, size_t *sindex)
{
	int		c;
	char	*temp;

	while (1)
	{
		c = string[*sindex];
		if (!c || c == '"')
			break ;
		(*sindex)++;
		if (c == '$')
		{
			temp = param_expand(shell, string, sindex);
			(void)(!temp || ft_strgenstr(strgen, temp));
			free(temp);
			if (!temp)
				return (FATAL_ERR);
		}
		else if (ft_strgenchr(strgen, c))
			return (FATAL_ERR);
	}
	if (c)
		(*sindex)++;
	return (0);
}
