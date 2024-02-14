#include "lexer.h"
#include "parser.h"
#include "shell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	print_command(t_command *command, int level);
void	print_heredoc(t_heredoc *heredoc);

int	main(void)
{
	int ret;
	char *line;
	t_lexical *lexical;
	t_command *command;
	t_heredoc *heredoc;

	while (1)
	{
		line = minishell_readline(PS1, isatty(0) && isatty(2));
		if (g_interrupt_state)
			continue ;
		if (!line)
			break ;
		ret = lexer(line, &lexical);
		free(line);
		if (ret == -1)
			break ;
		ret = parser(lexical, &command, &heredoc);
		dispose_lexical(lexical);
		if (ret == -1)
			break ;
		ret = gather_heredoc(heredoc, isatty(0) && isatty(2));
		if (ret == -1)
			break ;
		if (ret)
		print_command(command, 0);
		print_heredoc(heredoc);
		dispose_command(command);
		dispose_heredoc(heredoc);
	}
	printf("exit\n");
	return (0);
}