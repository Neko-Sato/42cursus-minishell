/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:26:35 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/16 12:03:35 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "shell.h"
#include "variable.h"
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

static int	search_for_command_internal(char *path, char *pathname,
				char **result);

int	search_for_command(t_minishell *shell, char *pathname, char **result)
{
	int		ret;
	char	*path;

	*result = NULL;
	path = getvar(shell->envp, "PATH");
	if (!path)
		return (0);
	path = ft_strdup(path);
	if (!path)
		return (-1);
	ret = search_for_command_internal(path, pathname, result);
	free(path);
	return (ret);
}

static int	search_for_command_internal(char *path, char *pathname,
		char **result)
{
	char	*temp;

	while (1)
	{
		temp = ft_strsep(&path, ":");
		if (!temp)
			break ;
		temp = ft_joinpath(temp, pathname);
		if (!temp)
			return (-1);
		if (!access(temp, F_OK))
			break ;
		free(temp);
	}
	*result = temp;
	return (0);
}
