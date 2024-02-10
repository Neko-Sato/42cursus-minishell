#include "lexer.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int			ret;
	char		*line;
	t_lexical	*lexical;

	while (1)
	{
		line = readline(">>> ");
		if (!line)
			break ;
		ret = lexer(line, &lexical);
		free(line);
		if (ret == -1)
			return (1);
		if (ret)
			continue;
		for (t_lexical *temp = lexical; temp; temp = temp->next)
		{
			if (temp->token == TK_WORD)
				printf("%s ", temp->value);
			else
				printf("{token %s} ", (char *[]){"", "", "<", "<<", ">", ">>", "|",
						"||", "&&", "(", ")"}[temp->token]);
		}
		printf("\n");
		lexical_dispose(lexical);
	}
	return (0);
}