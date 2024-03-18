#include "shell.h"
#include <libft.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	shell;
	int			ret;

	(void)argc;
	(void)argv;
	shell_init(&shell, envp);
	ret = reader_loop(&shell);
	shell_deinit(&shell);
	return (ret);
}
