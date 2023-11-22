/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:59:17 by hshimizu          #+#    #+#             */
/*   Updated: 2023/11/22 12:57:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include <libft.h>
#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	char cmd[]= "cat -e <<EOF | grep \"a a\"";
	// "cat", "-e", HERE_DOC, "EOF", PIPE, "grep", "a a"
	t_lex lex[]= lexer(cmd);

	printf("==lexer_test==\n");
	for (int i=0; lex[i]; i++)
		printf("%d: %s\n", i, lex[i].label);
	return 0;
}
