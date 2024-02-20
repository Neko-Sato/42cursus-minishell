# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/20 00:51:30 by hshimizu          #+#    #+#              #
#    Updated: 2024/02/20 05:04:50 by hshimizu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

DIR				= .
FT				= $(DIR)/libft
READLINE		= $(DIR)/readline
INCS_DIR		= $(DIR)/incs
SRCS_DIR		= $(DIR)/srcs
OBJS_DIR		= $(DIR)/objs

MAIN			= $(DIR)/main.c

SRCS			= \
	$(addprefix $(SRCS_DIR)/, \
		debug.c \
		readline.c \
		token.c \
		command_make.c \
		command_dispose.c \
		lexer.c \
		parser_element.c \
		parser_command.c \
		parser.c \
		heredoc.c \
	) \

OBJS			= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CFLAGS			= -Wall -Wextra -Werror -g
LDFLAGS			+= -L$(FT) -L$(READLINE)
IDFLAGS			+= -I$(FT) -I$(READLINE) -D READLINE_LIBRARY
LIBS			+= -lft -lreadline -ltermcap
IDFLAGS			+= -I$(INCS_DIR)

.PHONY: all clean fclean re bonus

all: $(FT) $(READLINE) $(NAME)

$(NAME): $(MAIN) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(IDFLAGS) $^ -o $@ $(LIBS)

bonus: all

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(IDFLAGS) $< -o $@

clean: $(READLINE)/Makefile
	$(RM) -r $(OBJS_DIR)
	@make -C $(READLINE) clean
	@make -C $(FT) clean

fclean: clean
	@make -C $(FT) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: test
test: test.c $(OBJS)
	$(CC) -g -fsanitize=address  $(LDFLAGS) $(IDFLAGS) $^ -o $@ $(LIBS)

.PHONY: norm
norm: $(MAIN) $(SRCS) $(INCS_DIR)
	@make -C $(FT) norm
	@norminette $^

.PHONY: $(FT)
$(FT):
	@git submodule update --init $@
	@$(MAKE) -C $@

$(READLINE)/Makefile: 
	(cd $(READLINE); ./configure CFLAGS=-w;)

.PHONY: $(READLINE)
$(READLINE): $(READLINE)/Makefile
	@git submodule update --init $@
	@$(MAKE) -C $@
