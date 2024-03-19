/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:44:32 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 18:32:41 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>

int	builtin_env(t_minishell *shell, t_wordlist *wordlist)
{
	(void)shell;
	(void)wordlist;
	ft_putendl_fd(wordlist->word, 1);
	return (0);
}

// #include "shell.h"
// #include <libft.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// static int	_main(int argc, char *argv[], char *envp[]);

// int	builtin_env(t_minishell *shell, t_wordlist *wordlist)
// {
// 	int		ret;
// 	char	**temp;
// 	int		argc;
// 	char	**argv;
// 	char	**envp;

// 	temp = wordlist2strarray(wordlist);
// 	if (!temp)
// 		return (-1);
// 	argc = ft_arrylen((void *)temp);
// 	argv = ft_strarrydup(temp);
// 	free(temp);
// 	if (!argv)
// 		return (-1);
// 	envp = ft_strarrydup(shell->envp);
// 	if (!envp)
// 	{
// 		free(argv);
// 		return (-1);
// 	}
// 	ret = _main(argc, argv, envp);
// 	ft_2darraydel(argv);
// 	ft_2darraydel(envp);
// 	return (ret);
// }

// static int	_main(int argc, char *argv[], char *envp[])
// {
// 	size_t	i;

// 	i = ;
// 	while (/* condition */)
// 	{
// 		/* code */
// 	}
// 	argv[]
// }
