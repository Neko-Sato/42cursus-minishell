/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:01:56 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 22:34:18 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "variable.h"
#include <libft.h>
#include <stdio.h>
#include <unistd.h>

// bash: cd: HOME not set
// bash: cd: OLDPWD not set
// bash: cd: too many arguments
int	builtin_cd(t_minishell *shell, t_wordlist *wordlist)
{
	char	*path;
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
	{
		perror("minishell: cd: ");
		return (1);
	}
	wordlist = wordlist->next;
	if (!wordlist)
	{
		path = getvar(shell->envp, "HOME");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (1);
		}
	}
	else if (!ft_strcmp("-", wordlist->word))
	{
		path = getvar(shell->envp, "OLDPWD");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (1);
		}
	}
	else if (wordlist->next)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	else
		path = wordlist->word;
	if (setvar(&shell->envp, "OLDPWD", current_dir, 1))
		return (1);
	ft_putendl_fd(wordlist->word, 1);
	return (0);
}
