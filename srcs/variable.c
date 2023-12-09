/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:44:40 by hshimizu          #+#    #+#             */
/*   Updated: 2023/12/09 20:07:41 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variable.h"
#include <libft.h>
#include <stdlib.h>

/*
	need use ft_vector
	Initialize with the following code
	```
	char **vars;

	vars = ft_vector(sizeof(char *), (char *[]){NULL}, 1);
	```

	And the deletion will be in the following code
	```
	size_t i;

	i = 0;
	while (vars[i])
		free(vars[i++]);
	ft_vector_del(vars);
	```
*/

static size_t	getindex(char **vars, char *key);

char	*getvar(char **vars, char *key)
{
	size_t	index;

	index = getindex(vars, key);
	if (vars[index])
		return (&vars[index][ft_strlen(key) + 1]);
	return (NULL);
}

int	putvar(char ***vars_ptr, char *string)
{
	int		result;
	char	*name_end;
	char	*name;

	name_end = ft_strchr(string, '=');
	if (!name_end)
		return (1);
	name = ft_substr(string, 0, name_end - string);
	if (!name)
		return (-1);
	result = setvar(vars_ptr, name, name_end + 1, 1);
	free(name);
	return (result);
}

int	setvar(char ***vars_ptr, char *key, char *value, int overwrite)
{
	size_t	index;
	size_t	size;
	char	*new_var;

	index = getindex(*vars_ptr, key);
	if ((*vars_ptr)[index] && !overwrite)
		return (1);
	size = ft_strlen(key) + ft_strlen(value) + 2;
	new_var = malloc(size);
	if (!new_var)
		return (-1);
	*new_var = '\0';
	ft_strlcat(new_var, key, size);
	ft_strlcat(new_var, "=", size);
	ft_strlcat(new_var, value, size);
	if (!(*vars_ptr)[index])
		return (ft_vector_insert(vars_ptr, index, &new_var, 1));
	free((*vars_ptr)[index]);
	(*vars_ptr)[index] = new_var;
	return (0);
}

int	unsetvar(char **vars, char *key)
{
	size_t	index;

	index = getindex(vars, key);
	if (!vars[index])
		return (1);
	free(vars[index]);
	ft_vector_erase(vars, index, 1);
	return (0);
}

static size_t	getindex(char **vars, char *key)
{
	size_t	i;
	size_t	keylen;

	keylen = ft_strlen(key);
	i = 0;
	while (vars[i])
	{
		if (!ft_strncmp(vars[i], key, keylen) && vars[i][keylen] == '=')
			break ;
		i++;
	}
	return (i);
}
