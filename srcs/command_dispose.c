/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_dispose.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:31:11 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/11 12:27:30 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <stdlib.h>

void	dispose_command(t_command *command)
{
	if (!command)
		return ;
	if (command->type == CT_SIMPLE)
	{
		dispose_wordlist(command->value.simplecom->wordlist);
		dispose_redirect(command->value.simplecom->redirect);
		free(command->value.simplecom);
	}
	else if (command->type == CT_GROUP)
	{
		dispose_command(command->value.groupcom->command);
		free(command->value.groupcom);
	}
	else if (command->type == CT_CONNCOM)
	{
		dispose_command(command->value.conncom->command1);
		dispose_command(command->value.conncom->command2);
		free(command->value.conncom);
	}
	free(command);
}

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
