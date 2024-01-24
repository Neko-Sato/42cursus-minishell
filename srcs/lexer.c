/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:35:24 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/18 20:20:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <libft.h>
#include <stddef.h>

/*
	ここにreadlineもぶち込もうか、字句リストを返します

	リダイレクトとパイプ
	セミコロン
	&&と||
	はtokenとして

	引用符とbackslash
	は字句解析時にいじる引用符はそのままバックスラッシュは消す

	here-docが着たらタグ付けする
*/

t_token	**lexer(t_line_fn line_fn)
{
	char	*line;
	t_token	**lexical;

	lexical = ft_vector(sizeof(t_token *), NULL, 0);
	if (!lexical)
		return (NULL);
	if (__lexer(&lexical, line_fn))
	{
		ft_vector()
		return (NULL);
	}
	return (lexical);
}

static int	__lexer(t_token **lexical, t_line_fn line_fn)
{
}

/*
cat -e <<EOF | grep abc
abc
efg
EOF

よくわかんえねぇけど字句解析したい

例えば
```
cat -e "文字列 mojiretu string$VAR"
```
が来た時
word: "cat"
word: "-e"
word: "\"文字列 mojiretu string$VAR\""
ってなるようにだとか
変数は、実行時に展開する
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
