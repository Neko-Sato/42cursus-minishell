# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/20 00:51:30 by hshimizu          #+#    #+#              #
#    Updated: 2024/03/08 01:14:50 by hshimizu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= minishell

DIR				:= .
FT				:= $(DIR)/libft
READLINE		:= $(DIR)/readline
INCS_DIR		:= $(DIR)/incs
SRCS_DIR		:= $(DIR)/srcs
OUT_DIR			:= $(DIR)/out

MAIN			:= $(DIR)/main.c

SRCS			:= \
	$(addprefix $(SRCS_DIR)/, \
		debug.c \
		shell.c \
		readline.c \
		token.c \
		wordlist.c \
		command_make.c \
		command_execute.c \
		command_dispose.c \
		command.c \
		lexer.c \
		parser_element.c \
		parser_command.c \
		parser.c \
		heredoc.c \
		glob_vector.c \
		glob_filename.c \
		glob.c \
		subst_param.c \
		subst_quote.c \
		subst_shell_case.c \
		subst_shell.c \
		subst_wordlist_split.c \
		subst_glob.c \
		subst.c \
		jobs.c \
	) \

OBJS			:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS			:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.d))

CFLAGS			:= -Wall -Wextra -Werror -g
LDFLAGS			:= -L$(FT) -L$(READLINE)/shlib
IDFLAGS			:= -I$(FT) -I$(READLINE) -D READLINE_LIBRARY
LIBS			:= -lft -lreadline -ltermcap
IDFLAGS			+= -I$(INCS_DIR)

.PHONY: all clean fclean re bonus

all: $(FT) $(READLINE) $(NAME)

$(NAME): $(MAIN) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(IDFLAGS) $^ -o $@ $(LIBS)

bonus: all

$(OUT_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -MMD -MP $(IDFLAGS) $< -o $@

clean: $(READLINE)/Makefile
	$(RM) -r $(OUT_DIR)
	@make -C $(READLINE) clean
	@make -C $(FT) clean

fclean: clean
	@make -C $(FT) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: test
test: test.c $(OBJS)
	$(CC) -g -fsanitize=address $(LDFLAGS) $(IDFLAGS) $^ -o $@ $(LIBS)

.PHONY: norm
norm: $(MAIN) $(SRCS) $(INCS_DIR)
	@make -C $(FT) norm
	@norminette $^

.PHONY: $(FT)
$(FT):
	@git submodule update --init $@
	@$(MAKE) -C $@

.PHONY: $(READLINE)
$(READLINE):
	@git config http.sslVerify false
	@git submodule update --init $@
	@(cd $(READLINE); [ -f Makefile ] || ./configure CFLAGS=-w;)
	@sed -n '29p' $@/readline.h | grep -q '#include <stdio.h>' ||\
		sed -i.old '29s/.*/#include <stdio.h>\n&/' readline/readline.h
	@sed -n '29p' $@/rltypedefs.h | grep -q '#include <stdio.h>' ||\
		sed -i.old '29s/.*/#include <stdio.h>\n&/' $@/rltypedefs.h
	@$(MAKE) -C $@

-include $(DEPS)
