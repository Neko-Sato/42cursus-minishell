/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:02:37 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/20 17:18:06 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "variable.h"
#include <libft.h>
#include <unistd.h>

int	builtin_unset(t_minishell *shell, t_wordlist *wordlist)
{
	int		status;
	char	*temp;

	status = 0;
	while (wordlist)
	{
		temp = wordlist->word;
		if (ft_strchr(temp, '='))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd("unset: not a valid identifier: ", STDERR_FILENO);
			ft_putendl_fd(temp, STDERR_FILENO);
			status = 1;
		}
		else
			unsetvar(shell->envp, temp);
		wordlist = wordlist->next;
	}
	return (status);
}
