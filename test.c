#include "shell.h"

int	main(void)
{
	t_minishell	shell;

	shell_init(&shell, NULL);
	return (reader_loop(&shell));
}
