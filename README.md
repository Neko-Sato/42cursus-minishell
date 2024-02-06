shell.h
シェルの変数の定義、reader_loop
lexer.h
字句解析
paser.h
構文解析
subst.h
文字列展開
cmmand.h
コマンドの生成や破棄
eval.h
コマンドの実行
prompt.h
プロンプト
builtin.h
ビルトイン定義
variable.h
変数の追加や削除 


- プロンプト作る
- 履歴作る
- 環境変数PATH(コマンド)と相対パス、絶対パスを何とか
- signalで死なないように？する

- 閉じていない引用符や、;（セミコロン）やバックスラッシュのような対象が必要としない特殊文字を解釈しない。
を解釈しない。

- 「'」と「"」の実装

- パイプとRedirectの実装 [<, >, <<, >>, |]

- $を使ってなんとか環境変数

- $?の実装(シェルが最後に実行したコマンドの終了状態)

- ctrl-C, ctrl-D and ctrl-\ (SIGINT, EOF, SIGQUIT)

- ビルドインたち
  - echo with option -n
  - cd
  - pwd, export, unset, env, exit(オプションなし)

- && と || 
- ワイルドカード

多分字句解析時にhere-docが着たら別のところにメモしておかないといけない
この後行を持っていきたいって言うのを実行時に

# 使用可能変数
関数名|説明
----|----
readline |普通に改行まで読む
rl_clear_history
rl_on_new_line |Ctr+C用かな
rl_replace_line
rl_redisplay
add_history|履歴の追加
printf
malloc
free
write
access
open
read
close
fork
wait
waitpid
wait3
wait4
signal
sigaction
sigemptyset
sigaddset
kill
exit
getcwd
chdir
stat
lstat
fstat
unlink
execve
dup
dup2
pipe
opendir
readdir
closedir
strerror
perror
isatty|ttyか調べるこいつが0だったらプロンプトらを表示させないエラーは履いたほうが良いかも？こいつがFalseなら即終了かな？
ttyname
ttyslot
ioctl
getenv
tcsetattr
tcgetattr
tgetent
tgetflag
tgetnum
tgetstr
tgoto
tputs