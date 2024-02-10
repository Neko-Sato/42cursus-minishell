/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:45:45 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/10 12:39:07 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <stdlib.h>

t_command	*make_simplecom(t_wordlist *wordlist, t_redirect *redirect)
{
	t_command	*ret;
	t_simplecom	*simplecom;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return (NULL);
	simplecom = malloc(sizeof(*simplecom));
	if (!simplecom)
	{
		free(ret);
		return (NULL);
	}
	ret->type = (t_redirecttype []){CT_SIMPLE, CT_NONE}[!wordlist];
	ret->value.simplecom = simplecom;
	simplecom->wordlist = wordlist;
	simplecom->redirect = redirect;
	return (ret);
}

t_command	*make_conncom(t_concomtype type, t_command *command1,
		t_command *command2)
{
	t_command	*ret;
	t_conncom	*conncom;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return (NULL);
	conncom = malloc(sizeof(*conncom));
	if (!conncom)
	{
		free(ret);
		return (NULL);
	}
	ret->type = CT_CONNCOM;
	ret->value.conncom = conncom;
	conncom->type = type;
	conncom->command1 = command1;
	conncom->command2 = command2;
	return (ret);
}

t_command	*make_groupcom(t_command *command)
{
	t_command	*ret;
	t_groupcom	*groupcom;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return (NULL);
	groupcom = malloc(sizeof(*groupcom));
	if (!groupcom)
	{
		free(ret);
		return (NULL);
	}
	ret->type = CT_GROUP;
	ret->value.groupcom = groupcom;
	groupcom->command = command;
	return (ret);
}
