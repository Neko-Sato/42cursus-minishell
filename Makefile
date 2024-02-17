# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/20 00:51:30 by hshimizu          #+#    #+#              #
#    Updated: 2024/02/17 19:14:00 by hshimizu         ###   ########.fr        #
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
		lexer_skip.c \
		lexer.c \
		parser_element.c \
		parser_command.c \
		parser.c \
	) \

OBJS			= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CFLAGS			= -Wall -Wextra -Werror
LDFLAGS			+= -L$(FT) -L$(READLINE)
IDFLAGS			+= -I$(FT) -I$(READLINE)
LIBS			+= -lft -lreadline -ltermcap
IDFLAGS			+= -I$(INCS_DIR)

.PHONY: all clean fclean re bonus

all: $(FT) $(NAME)

$(NAME): $(MAIN) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(IDFLAGS) $^ -o $@ $(LIBS)

bonus: all

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(IDFLAGS) $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)
	@make -C $(FT) clean
	@make -C $(READLINE) clean

fclean: clean
	@make -C $(FT) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: test
test: test.c $(OBJS)
	$(CC) -g $(LDFLAGS) $(IDFLAGS) $^ -o $@ $(LIBS)

.PHONY: norm
norm: $(MAIN) $(SRCS) $(INCS_DIR)
	@make -C $(FT) norm
	@norminette $^

.PHONY: $(FT)
$(FT):
	@git submodule update --init $@
	@$(MAKE) -C $@

$(READLINE)/Makefile: 
	(cd $(READLINE); ./configure;)

.PHONY: $(READLINE)
$(READLINE): $(READLINE)/Makefile
	@git submodule update --init $@
	@$(MAKE) -C $@
