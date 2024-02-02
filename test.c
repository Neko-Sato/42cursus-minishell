#include "minishell.h"
#include "lexer.h"
#include "prompt.h"
#include <libft.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

int	main(void)
{
	t_minishell gvars;
	char *line, *temp;
	t_xlst *lst;
	size_t start, pos;

	rl_outstream = stderr;
	gvars.envp = NULL;
	gvars.vars = NULL;
	gvars.isinteractive = 1;
	line = NULL;
	lst = NULL;

	while (1)
	{
		pos = 0;
		line = put_primary_prompt(&gvars);
		if (!line)
		{
			ft_putendl_fd("exit", 2);
			break ;
		}
		while (line[pos])
		{
			get_word(&line, &pos, &temp);
			if (temp)
				ft_xlstappend(&lst, &temp, sizeof(char *));	
		}
		while (lst)
		{
			ft_xlstpop(&lst, 0, &temp, sizeof(char *));
			printf("%s ", temp);
			free(temp);
		}
		printf("\n");
		free(line);
	}
}