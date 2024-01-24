#include <libft.h>

typedef enum e_redirecttype
{
	r_redirect,
	r_here_doc,
	r_append,
	r_overwrite,
}						t_redirecttype;

typedef struct s_redirect
{
	struct s_redirect	*next;
	t_redirecttype		type;
	char				*filename;
}						t_redirect;

typedef enum e_commandtype
{
	c_simple,
	c_conncom,
}						t_commandtype;

typedef struct s_simplecom
{
	t_redirect			*redirect;
	t_list				*wordlist;
}						t_simplecom;

typedef enum e_concomtype
{
	cc_and,
	cc_or,
	cc_pipe,
	cc_end,
}						t_concomtype;

typedef struct s_conncom
{
	t_concomtype		concomtype;
	struct s_command	*command1;
	struct s_command	*command2;
}						t_conncom;

typedef struct s_command
{
	t_commandtype		type;
	t_redirect			*redirect;
	union
	{
		t_simplecom		simplecom;
		t_conncom		conncom;
	} value;
}						t_command;

typedef struct s_minishell
{
	char				**envp;
	char				**vars;
	int					isttay;
	t_command			*command;
	t_list				*herdoc_tag;
}						t_minishell;

int						reader_loop(t_minishell *vars);

int						read_command(t_minishell *vars);
int						parse_command(t_minishell *vars);
//解放用
int						dispose_command(t_command *command);
int						execute_command(t_command *command);

/*
改行コードが着たらloopを抜ける
バックスラッシュのち改行は改行が無視される
文字列がNULLだったらprimarypromptを表示し、
ヌル文字になるったらsecondarypromptを表示する。
処理の所で文字列をいろいろコピーし、リスト状かtree上にする
