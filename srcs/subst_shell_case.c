/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_shell_case.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 21:34:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/20 15:56:23 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "subst.h"
#include "variable.h"
#include <libft.h>
#include <stdlib.h>

int	case_singlequote(t_minishell *shell, t_strgen *strgen, char *string,
		size_t *sindex)
{
	int		ret;
	char	*temp;
	char	*temp1;

	temp = string_extract_single_quoted(shell, string, sindex);
	if (!temp)
		return (-1);
	temp1 = quote_string(temp);
	free(temp);
	if (!temp1)
		return (-1);
	ret = ft_strgenstr(strgen, temp1);
	free(temp1);
	return (ret);
}

int	case_doublequote(t_minishell *shell, t_strgen *strgen, char *string,
		size_t *sindex)
{
	int		ret;
	char	*temp;
	char	*temp1;

	temp = string_extract_double_quoted(shell, string, sindex);
	if (!temp)
		return (-1);
	temp1 = quote_string(temp);
	free(temp);
	if (!temp1)
		return (-1);
	ret = ft_strgenstr(strgen, temp1);
	free(temp1);
	return (ret);
}

int	case_tilde(t_minishell *shell, t_strgen *strgen, char *string,
		size_t *sindex)
{
	int		ret;
	char	*temp;

	if (*sindex - 1 != 0 || !ft_strchr("/", string[*sindex]))
		return (ft_strgenchr(strgen, '~'));
	temp = quote_string((char *)getvar(shell->envp, "HOME"));
	if (!temp)
		return (-1);
	ret = ft_strgenstr(strgen, temp);
	free(temp);
	return (ret);
}

int	case_dollar(t_minishell *shell, t_strgen *strgen, char *string,
		size_t *sindex)
{
	int		ret;
	char	*temp;

	temp = param_expand(shell, string, sindex);
	if (!temp)
		return (SYSTEM_ERR);
	ret = ft_strgenstr(strgen, temp);
	free(temp);
	return (ret);
}
