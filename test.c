#include "lexer.h"
#include "parser.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

void	print_command(t_command *command, int level);

void	print_redirect(t_redirect *redirect, int level)
{
	if (!redirect)
		return ;
	printf("%*sRedirect Type: %s, Word: %s\n", level * 4, "",
			(char *[]){"INPUT", "HEREDOC", "OVERWRITE",
			"APPEND"}[redirect->type], redirect->word);
	print_redirect(redirect->next, level);
}

void	print_wordlist(t_wordlist *wordlist, int level)
{
	if (!wordlist)
		return ;
	printf("%*sWord: %s\n", level * 4, "", wordlist->word);
	print_wordlist(wordlist->next, level);
}

void	print_simplecom(t_simplecom *simplecom, int level)
{
	if (!simplecom)
		return ;
	printf("%*sSimple Command:\n", level * 4, "");
	print_redirect(simplecom->redirect, level + 1);
	print_wordlist(simplecom->wordlist, level + 1);
}

void	print_conncom(t_conncom *conncom, int level)
{
	if (!conncom)
		return ;
	printf("%*sConnection Command:\n", level * 4, "");
	printf("%*sType: %s\n", (level + 1) * 4, "", (char *[]){"PIPE", "AND",
			"OR"}[conncom->type]);
	printf("%*sCommand 1:\n", (level + 1) * 4, "");
	print_command(conncom->command1, level + 1);
	printf("%*sCommand 2:\n", (level + 1) * 4, "");
	print_command(conncom->command2, level + 1);
}

void	print_groupcom(t_groupcom *groupcom, int level)
{
	if (!groupcom)
		return ;
	printf("%*sGroup Command:\n", level * 4, "");
	print_command(groupcom->command, level + 1);
}

void	print_command(t_command *command, int level)
{
	if (!command)
		return ;
	switch (command->type)
	{
	case CT_SIMPLE:
		print_simplecom(command->value.simplecom, level);
		break ;
	case CT_CONNCOM:
		print_conncom(command->value.conncom, level);
		break ;
	case CT_GROUP:
		print_groupcom(command->value.groupcom, level);
		break ;
	}
}

void	print_heredoc(t_heredoc *heredoc)
{
	if (!heredoc)
		return ;
	printf("heredoc : %s\n", heredoc->eof);
	print_heredoc(heredoc->next);
}

int	main(void)
{
	int ret;
	char *line;
	t_lexical *lexical;
	t_command *command;
	t_heredoc *heredoc;

	while (1)
	{
		line = readline(">>> ");
		if (!line)
			break ;
		ret = lexer(line, &lexical);
		free(line);
		if (ret)
			break ;
		ret = parser(lexical, &command, &heredoc);
		dispose_lexical(lexical);
		if (ret)
			break ;
		print_command(command, 0);
		print_heredoc(heredoc);
		dispose_command(command);
	}
	printf("exit\n");
	return (0);
}