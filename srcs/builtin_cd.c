/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:01:56 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 18:32:49 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>

int	builtin_cd(t_minishell *shell, t_wordlist *wordlist)
{
	(void)shell;
	(void)wordlist;
	ft_putendl_fd(wordlist->word, 1);
	return (0);
}
