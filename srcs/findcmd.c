/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:26:35 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/12 16:25:30 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "shell.h"
#include "variable.h"

/*
	ここではコマンドのpathを検索する
	コマンドにはもちろん"/"は含まれない
	PTAHから探す。

	システムエラー時もnotfoud時もNULLを返します
	errnoで区別させるのでerrnoを実行前に初期化してください
*/

char	*search_for_command(t_minishell *shell, char *pathname)
{
	char *path;
	char *paths;

	path = getvar(shell->envp, "PATH");
	if (!path)
		return (NULL);

}