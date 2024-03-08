#include "shell.h"
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	t_minishell	shell;
	int			ret;

	printf("misnishell pid -> %d\n\n", getpid());
	shell_init(&shell, NULL);
	ret = reader_loop(&shell);
	shell_deinit(&shell);
	return (ret);
}
