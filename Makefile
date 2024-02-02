# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/20 00:51:30 by hshimizu          #+#    #+#              #
#    Updated: 2024/02/02 08:39:08 by hshimizu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

DIR				= .
FT				= $(DIR)/libft
INCS_DIR		= $(DIR)/incs
SRCS_DIR		= $(DIR)/srcs
OBJS_DIR		= $(DIR)/objs

MAIN			= $(DIR)/main.c

SRCS			= \
	$(addprefix $(SRCS_DIR)/, \
		prompt.c \
		lexer.c \
	) \

OBJS			= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CFLAGS			= -Wall -Wextra -Werror
LDFLAGS			+= -L$(FT)
IDFLAGS			+= -I$(FT)
LIBS			+= -lft -lreadline
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

fclean: clean
	@make -C $(FT) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: test
test: test.c $(OBJS)
	$(CC) -g  $(LDFLAGS) $(IDFLAGS) $^ -o $@ $(LIBS)

.PHONY: norm
norm: $(MAIN) $(SRCS) $(INCS_DIR)
	@make -C $(FT) norm
	@norminette $^

.PHONY: $(FT)
$(FT):
	@git submodule update --init $@
	@$(MAKE) -C $@