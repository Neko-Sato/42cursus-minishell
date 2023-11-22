/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:59:17 by hshimizu          #+#    #+#             */
/*   Updated: 2023/11/22 13:17:26 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include <libft.h>
#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	char	*label;
	t_lex	**lex;

	lex = lexer("cat -e <<EOF | grep \"a a\"");
	// "cat", "-e", HERE_DOC, "EOF", PIPE, "grep", "a a"
	printf("==lexer_test==\n");
	for (int i = 0; lex[i]; i++)
	{
		label = "";
		printf("%d: %s\n", i, label);
	}
	return (0);
}
