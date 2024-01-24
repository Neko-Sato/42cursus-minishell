/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordtoken_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:12:45 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/18 19:54:57 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

/*
	Further split Word tokens
	Expands quotes, variables, and asterisks and returns a string array

	Just before execution,
		it is used to convert a Wordtoken into a string array, for example
*/

typedef int	(*t_case_fn)(t_strgen *temp, char *str);

static int	case_quote(t_strgen *temp, char *str);
static int	case_doublequote(t_strgen *temp, char *str);
static int	case_dollar(t_strgen *temp, char *str);
static int	case_asterisk(t_strgen *temp, char *str);

const char	*g_case = {'\'', '"', '$', '*'};

char	**wordexp(t_minishell *minishell, char *str)
{
	int			err;
	char		*result;
	t_strgen	*temp;

	temp = ft_strgennew();
	if (!temp)
		return (NULL);
	while (*str)
	{
		t = case - ft_strnchr(case, *str, 4);
		if (t < 0)
			str++;
	}
	if (!*str)
		result = ft_strgencomp(temp);
	ft_strgendel(temp);
	return (result);
}
