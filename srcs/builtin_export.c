/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:02:37 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/20 19:11:21 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "variable.h"
#include <libft.h>
#include <stdlib.h>

static int	export_noargs(t_minishell *shell);

int	builtin_export(t_minishell *shell, t_wordlist *wordlist)
{
	if (!wordlist)
		return (export_noargs(shell));
	while (wordlist)
	{
		if (putvar(&shell->envp, wordlist->word) == -1)
			return (-1);
		wordlist = wordlist->next;
	}
	return (EXIT_SUCCESS);
}

static int	export_noargs(t_minishell *shell)
{
	return (0);
}

// static int	need_escape(char *str)
// {
// 	if (!*str)
// 		return (1);
// 	return (!!ft_strpbrk(str, "<>&|()*\"~ "));
// }

// static char	*escape(char *str)
// {
// 	char		*result;
// 	t_strgen	*strgen;

// 	strgen = ft_strgennew(STRGEN_BUUFERSIZE);
// 	if (!strgen)
// 		return (NULL);
// 	if (ft_strgenchr(strgen, '\''))
// 		result = ft_strgencomp(strgen);
// 	ft_strgendel(strgen);
// 	return (result);
// }

// static int	_print_environ(void)
// {
// }