/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_filename.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:19:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/01 02:15:16 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include <libft.h>
#include <stdlib.h>

/*汚いコードの可読性を上げなければ、、、*/

static char	**globfilename_internal(char *dirname, char *filename);
static char	**only_filename(char *dirname, char *filename);
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

static char	**only_filename(char *dirname, char *filename)
{
	char	**temp;
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
	temp = glob_vector(filename, (char *[]){dirname, "."}[!dirname]);
	if (dirname)
		result = glob_dir_to_array(dirname, temp);
	else
		result = temp;
	if (!result)
		ft_2darraydel(temp);
	free(dirname);
	return (result);
}

int			__(t_xlst **lst_ptr, char **dirs, char *filename);

static char	**globfilename_internal(char *dirname, char *filename)
{
	t_xlst	*lst;
	int		ret;
	void	*temp;
	char	**result;

	temp = globfilename(dirname);
	if (!temp)
		return (NULL);
	lst = NULL;
	ret = __(&lst, temp, filename);
	ft_2darraydel(temp);
	result = NULL;
	if (!ret)
		result = ft_xlst2array(lst, sizeof(char *), NULL);
	if (!result)
		while (!ft_xlstpop(&lst, 0, &temp, sizeof(char *)))
			free(temp);
	ft_xlstclear(&lst);
	return (result);
}

int	__(t_xlst **lst_ptr, char **dirs, char *filename)
{
	void *temp;
	char **result;

	while (*dirs)
	{
		if (glob_testdir(*dirs) == 0)
		{
			if (*filename)
			{
				temp = glob_vector(filename, *dirs);
				result = glob_dir_to_array(*dirs, temp);
				if (result && ft_xlstappendarry(lst_ptr, temp, ft_arrylen(temp),
						sizeof(char *)))
				{
					ft_2darraydel(temp);
					return (-1);
				}
				free(result);
			}
			else
			{
				temp = ft_joinpath(*dirs, "");
				if (temp && ft_xlstappend(lst_ptr, &temp, sizeof(char *)))
				{
					free(temp);
					return (-1);
				}
			}
		}
		dirs++;
	}
	return (0);
}