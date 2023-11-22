/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:35:24 by hshimizu          #+#    #+#             */
/*   Updated: 2023/11/22 14:51:27 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <libft.h>

/*
よくわかんえねぇけど字句解析したい

例えば
```
cat -e "文字列 mojiretu string"
```
が来た時
word: "cat"
word: "-e"
word: "\"文字列 mojiretu string\""
ってなるようにだとか
```
echo asd"aa ss" | cat
```
word: "echo"
word: "asd\"aa ss\""
pipe
word: "cat"
みたいなようにできるようにしたい
たぶんこれ

あとエスケープ
Redirectとかでくっついてるやつも引きはがしたい
<<EOF
<< EOF
ってやつ
*/

t_token	**lexer(char *str)
{
	return ((void *)0);
}