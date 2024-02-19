#include "lexer.h"
#include "parser.h"
#include "shell.h"
#include <stdio.h>
#include <readline.h>
#include <stdlib.h>
#include <unistd.h>

void	print_command(t_command *command, int level);
void	print_heredoc(t_heredoc *heredoc);

int	main(void)
{
	t_minishell	shell;

	shell.command = NULL;
	shell.envp = NULL;
	shell.line = 0;
	shell.heredoc = NULL;
	shell.isinteractive = isatty(0) && isatty(2);
	shell.last_status = 0;
	shell.sindex = 0;
	shell.string = NULL;

	parser(&shell);
	print_command(shell.command, 0);
	print_heredoc(shell.heredoc);
	dispose_command(shell.command);
	dispose_heredoc(shell.heredoc);
	free(shell.string);
	// int ret;
	// char *line;
	// t_lexical *lexical;
	// t_command *command;
	// t_heredoc *heredoc;

	// while (1)
	// {
	// 	line = minishell_readline(PS1, isatty(0) && isatty(2));
	// 	if (g_interrupt_state)
	// 		continue ;
	// 	if (!line)
	// 		break ;
	// 	ret = lexer(line, &lexical);
	// 	free(line);
	// 	if (ret == -1)
	// 		break ;
	// 	ret = parser(lexical, &command, &heredoc);
	// 	dispose_lexical(lexical);
	// 	if (ret == -1)
	// 		break ;
	// 	ret = gather_heredoc(heredoc, isatty(0) && isatty(2));
	// 	if (ret == -1)
	// 		break ;
	// 	print_command(command, 0);
	// 	print_heredoc(heredoc);
	// 	dispose_command(command);
	// 	dispose_heredoc(heredoc);
	// }
	// if (isatty(0) && isatty(2))
	// 	printf("exit\n");
	return (0);
}
