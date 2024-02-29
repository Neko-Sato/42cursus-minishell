/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:28:19 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/29 11:25:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static void	glob_match_wildcard(char *filename, char *pattern, size_t index[2]);

int	glob_match(char *filename, char *pattern)
{
	size_t	index[2];

	index[0] = 0;
	index[1] = 0;
	while (filename[index[0]])
	{
		if (pattern[index[1]] == '\\')
			index[1]++;
		else if (pattern[index[1]] == '*')
		{
			if (index[1] == 0 && filename[index[0]] == '.')
				return (0);
			glob_match_wildcard(filename, pattern, index);
		}
		else if (pattern[index[1]++] != filename[index[0]++])
			return (0);
	}
	while (pattern[index[1]] == '*')
		index[1]++;
	return (!pattern[index[1]]);
}

static void	glob_match_wildcard(char *filename, char *pattern, size_t index[2])
{
	size_t	pos[2];

	pos[0] = index[0];
	pos[1] = index[1]++;
	while (filename[index[0]])
	{
		if (pattern[index[1]] == '*')
			break ;
		if (pattern[index[1]++] != filename[index[0]++])
		{
			index[0] = ++pos[0];
			index[1] = pos[1] + 1;
		}
	}
}

int	glob_pattern(char *stirng)
{
	while (*stirng)
	{
		if (*stirng == '\\')
			if (*++stirng)
				break ;
		if (*stirng == '*')
			return (1);
		stirng++;
	}
	return (0);
}

int	glob_testdir(char *dir)
{
	struct stat	finfo;
	int			r;

	r = stat(dir, &finfo);
	if (r < 0)
		return (-1);
	if (S_ISDIR(finfo.st_mode) == 0)
		return (-1);
	return (0);
}
