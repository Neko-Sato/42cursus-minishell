/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:02:37 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/19 18:33:03 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <libft.h>

int	builtin_unset(t_minishell *shell, t_wordlist *wordlist)
{
	(void)shell;
	(void)wordlist;
	ft_putendl_fd(wordlist->word, 1);
	return (0);
}
