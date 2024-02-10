/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:31:11 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/10 23:45:46 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"
#include <stdlib.h>

void	dispose_wordlist(t_wordlist *wordlist)
{
	void	*temp;

	while (wordlist)
	{
		temp = wordlist;
		wordlist = wordlist->next;
		free(temp);
	}
}

void	dispose_redirect(t_redirect *redirect)
{
	void	*temp;

	while (redirect)
	{
		temp = redirect;
		redirect = redirect->next;
		free(temp);
	}
}
