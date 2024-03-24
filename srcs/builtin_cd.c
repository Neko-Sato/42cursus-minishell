/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:01:56 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 17:48:51 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "variable.h"
#include <errno.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PRINTPATH 0b01

static char	*getpath(t_minishell *shell, t_wordlist *wordlist, int *flag);
static int	printpath(char *path);
static int	set_environment(t_minishell *shell, char *path);

int	builtin_cd(t_minishell *shell, t_wordlist *wordlist)
{
	int		flag;
	char	*path;

	flag = 0;
	path = getpath(shell, wordlist, &flag);
	if (!path)
		return (EXIT_FAILURE);
	if (chdir(path))
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(path, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if ((flag & PRINTPATH) && printpath(path))
		return (EXIT_FAILURE);
	if (set_environment(shell, path))
		return (-1);
	return (EXIT_SUCCESS);
}

static char	*getpath(t_minishell *shell, t_wordlist *wordlist, int *flag)
{
	char	*result;

	result = NULL;
	if (!wordlist)
	{
		result = get_string_value(shell, "HOME");
		if (!result)
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	}
	else if (wordlist->next)
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
	else if (!ft_strcmp(wordlist->word, "-"))
	{
		*flag |= PRINTPATH;
		result = get_string_value(shell, "OLDPWD");
		if (!result)
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
	}
	else
		result = wordlist->word;
	return (result);
}

static int	printpath(char *path)
{
	int	err;

	err = write(STDOUT_FILENO, path, ft_strlen(path)) == -1;
	if (!err)
		err = write(STDOUT_FILENO, "\n", 1) == -1;
	if (err)
		perror("minishell: cd");
	return (err);
}

static int	set_environment(t_minishell *shell, char *path)
{
	char	*pwd;

	if (!bind_variable(shell, "OLDPWD", get_string_value(shell, "PWD"), 0))
		return (FATAL_ERR);
	pwd = getcwd(NULL, 0);
	if (!pwd && errno == ENOENT)
	{
		if (shell->cwd)
			pwd = ft_joinpath(shell->cwd, path);
		else
			pwd = ft_strdup(path);
	}
	if (!pwd && errno == ENOMEM)
		return (FATAL_ERR);
	else if (!pwd)
	{
		perror("minishell: cd: getcwd");
		return (SYSTEM_ERR);
	}
	free(shell->cwd);
	shell->cwd = pwd;
	if (!bind_variable(shell, "PWD", pwd, 0))
		return (FATAL_ERR);
	return (NOERR);
}
