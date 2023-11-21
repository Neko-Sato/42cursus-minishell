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

# 使用可能変数
関数名|説明
----|----
readline 
rl_clear_history
rl_on_new_line
rl_replace_line
rl_redisplay
add_history
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
isatty
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