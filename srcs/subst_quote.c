/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 23:01:14 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/24 23:59:43 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>

char	*quote_string(char *string)
{
	char	*head;
	char	*temp;

	if (!string)
		return (NULL);
	temp = malloc(ft_strlen(string) * 2 + 1);
	if (!temp)
		return (NULL);
	head = temp;
	while (*string)
	{
		*temp++ = '\1';
		*temp++ = *string++;
	}
	*temp = '\0';
	return (head);
}

char	*dequote_string(char *string)
{
	t_strgen	*strgen;
	char		*head;

	strgen = ft_strgennew(STRGEN_BUUFERSIZE);
	if (!strgen)
		return (NULL);
	while (*string)
	{
		if (*string == '\1')
		{
			if (!++*string)
				break ;
		}
		if (ft_strgenchr(strgen, *string++))
		{
			ft_strgendel(strgen);
			return (NULL);
		}
	}
	head = ft_strgencomp(strgen);
	ft_strgendel(strgen);
	return (head);
}
