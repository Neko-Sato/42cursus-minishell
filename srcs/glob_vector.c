/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 04:35:15 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/01 16:56:45 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include <dirent.h>
#include <libft.h>
#include <stdlib.h>

static char	**case_null_filename(char *dirname);
static int	glob_vector_internal(t_xlst **lst, DIR *dir, char *pattern);

char	**glob_vector(char *filename, char *dirname)
{
	int		ret;
	char	**result;
	t_xlst	*lst;
	DIR		*dir;
	char	*temp;

	if (!dirname)
		return (NULL);
	lst = NULL;
	if (!filename || !*filename)
		return (case_null_filename(dirname));
	dir = opendir(dirname);
	if (!dir)
		return (NULL);
	ret = glob_vector_internal(&lst, dir, filename);
	closedir(dir);
	result = NULL;
	if (!ret)
		result = ft_xlst2array(lst, sizeof(char *), NULL);
	if (!result)
		while (!ft_xlstpop(&lst, 0, &temp, sizeof(char *)))
			free(temp);
	ft_xlstclear(&lst);
	return (result);
}

static char	**case_null_filename(char *dirname)
{
	char	**result;
	char	*temp;

	if (glob_testdir(dirname) < 0)
		return (NULL);
	temp = ft_strdup("");
	if (!temp)
		return (NULL);
	result = ft_memdup((char *[]){temp, NULL}, sizeof(char *[2]));
	if (!result)
		free(temp);
	return (result);
}

static int	glob_vector_internal(t_xlst **lst_ptr, DIR *dir, char *pattern)
{
	struct dirent	*dp;
	char			*temp;

	dp = readdir(dir);
	while (dp)
	{
		if (glob_match(dp->d_name, pattern))
		{
			temp = ft_strdup(dp->d_name);
			if (ft_xlstappend(lst_ptr, &temp, sizeof(char *)))
			{
				free(temp);
				return (-1);
			}
		}
		dp = readdir(dir);
	}
	if (ft_xlstappend(lst_ptr, &(char *){NULL}, sizeof(char *)))
		return (-1);
	return (0);
}
