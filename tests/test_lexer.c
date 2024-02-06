#include "lexer.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char		*line;
	t_lexical	*lexical;
	line = readline(">>> ");
	if (lexer(line, &lexical))
		return 1;
	for (t_lexical	*temp = lexical; temp; temp = temp->next)
	{
		if (temp->token == TK_WORD)
			printf("%s ", temp->value);
		else 
			printf("%s ", (char *[]){
			"","","<","<<",">",">>", "|", "||", "&&", "(", ")"
			}[temp->token]);
	}
	lexical_dispose(lexical);
	return 0;
}