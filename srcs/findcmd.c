/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:26:35 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/24 13:05:53 by hshimizu         ###   ########.fr       */
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
	path = get_string_value(shell, "PATH");
	if (!path)
		return (NOERR);
	path = ft_strdup(path);
	if (!path)
		return (FATAL_ERR);
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
			return (FATAL_ERR);
		if (!access(temp, F_OK))
			break ;
		free(temp);
	}
	*result = temp;
	return (NOERR);
}
