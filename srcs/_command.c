/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 23:15:46 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/31 03:13:38 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "minishell.h"
#include "repl.h"
#include <libft.h>

int	reader_command(t_minishell *gvars, t_repl *vars)
{
	t_command	*command;
	size_t		start;
	int			c;

	while (1)
	{
		if (skip_space(gvars, &vars->line, &vars->pos))
			return (-1);
		start = vars->pos;
		while (1)
		{
			c = pgetc(gvars, &vars->line, vars->pos);
			// if (c == '\'')
			// 	skip_singlquote();
			// 	else if (c == '"')
			// 		skip_doublequote();
			// 	else if (!ft_strncmp("<", 1))
			// 		;
			// 	else if (!ft_strncmp("<<", 2))
			// 		;
			// 	else if (!ft_strncmp(">", 2))
			// 		;
			// 	else if (!ft_strncmp(">>", 2))
			// 		;
			// 	else if (!ft_strncmp("|", 1))
			// 		;
			// 	else if (!ft_strncmp("&&", 2))
			// 		;
			// 	else if (!ft_strncmp("||", 2))
			// 		;
			// 	else if (c == '\\')
			// 		;
			// 	else if (c == '\0')
			// 		;
			// }
		}
	}
	return (0);
}

