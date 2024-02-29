/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_filename.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:19:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/29 11:24:03 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include <libft.h>
#include <stdlib.h>

static char	**globfilename_internal(char *dirname, char *filename);
static char	**only_filename(char *dirname, char *filename);
static char	**glob_dir_to_array(char *dir, char **arry);
static void	dequote_pathname(char *string);

char	**globfilename(char *pattern)
{
	char	**result;
	char	*dirname;
	char	*filename;

	if (!pattern)
		return (NULL);
	dirname = NULL;
	filename = ft_strrchr(pattern, '/');
	if (filename)
	{
		dirname = ft_substr(pattern, 0, filename++ - pattern);
		if (!dirname)
			return (NULL);
	}
	else
		filename = pattern;
	if (dirname && glob_pattern(dirname))
		result = globfilename_internal(dirname, filename);
	else
		result = only_filename(dirname, filename);
	free(dirname);
	return (result);
}

static char	**only_filename(char *dirname, char *filename)
{
	char	**result;

	if (!*filename)
		return (ft_memdup((char *[]){NULL}, sizeof(char *[1])));
	if (dirname)
	{
		dirname = ft_joinpath(dirname, "");
		if (!dirname)
			return (NULL);
		dequote_pathname(dirname);
	}
	result = glob_vector(filename, (char *[]){dirname, "."}[!dirname]);
	if (result && dirname)
		result = glob_dir_to_array(dirname, result);
	free(dirname);
	return (result);
}

static char	**glob_dir_to_array(char *dir, char **arry)
{
	size_t	index;
	char	*temp;

	if (!dir || !arry)
		return (arry);
	index = 0;
	while (arry[index])
	{
		temp = ft_joinpath(dir, arry[index]);
		if (!temp)
		{
			ft_2darraydel(arry);
			return (NULL);
		}
		free(arry[index]);
		arry[index++] = temp;
	}
	return (arry);
}

static void	dequote_pathname(char *string)
{
	size_t	i;
	size_t	j;

	if (!string)
		return ;
	i = 0;
	j = 0;
	while (string[j])
	{
		if (string[j] == '\\')
			j++;
		else if (string[j] == '\'')
			j++;
		else if (string[j] == '"')
			j++;
		string[i++] = string[j++];
	}
}

/*
	こいつがやること
	dirs = globfilename(dirname);
	の結果でディレクトリのやつだけ集めてfilenameとjoinpathするのを
	一つのリストにする
*/
static char	**globfilename_internal(char *dirname, char *filename)
{
	(void)dirname;
	(void)filename;
	return (NULL);
}
