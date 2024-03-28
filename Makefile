# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/20 00:51:30 by hshimizu          #+#    #+#              #
#    Updated: 2024/03/28 21:50:17 by hshimizu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:= minishell

DIR					:= .
FT					:= $(DIR)/libft
READLINE			:= $(DIR)/readline
INCS_DIR			:= $(DIR)/incs
SRCS_DIR			:= $(DIR)/srcs
OUT_DIR				:= $(DIR)/out

SRCS				:= \
	$(addprefix $(SRCS_DIR)/, \
		main.c \
		init.c \
		shell.c \
		signal.c \
		readline.c \
		token.c \
		wordlist.c \
		command_make.c \
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
		jobs_fork.c \
		jobs_wait.c \
		findcmd.c \
		piping.c \
		redirect.c \
		execute_cmd.c \
		execute_pipeline.c \
		execute_simplecom.c \
		execute_null_command.c \
		execute_disk_command.c \
		execute_builtin.c \
		builtin_echo.c \
		builtin_env.c \
		builtin_cd.c \
		builtin_pwd.c \
		builtin_export.c \
		builtin_unset.c \
		builtin_exit.c \
		variable.c \
		variable_bind.c \
		variable_envp.c \
	) \

OBJS				:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS				:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.d))

CFLAGS				:= -Wall -Wextra -Werror
IDFLAGS				:= -I$(INCS_DIR)
LDFLAGS				:=

IDFLAGS				+= -I$(FT)
LDFLAGS				+= -L$(FT)
LIBS				+= -lft

IDFLAGS				+= -I$(READLINE)
LDFLAGS				+= -L$(READLINE)
LIBS 				+= -lreadline

.PHONY: all clean fclean re bonus

all: $(FT) $(READLINE) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(IDFLAGS) $^ -o $@ $(LIBS)

bonus: all

$(OUT_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -MMD -MP $(IDFLAGS) $< -o $@

clean:
	$(RM) -r $(OUT_DIR)
	@make -C $(FT) clean

fclean: clean
	@make -C $(FT) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: test
test: $(OBJS)
	$(CC) -g -fsanitize=address $(CFLAGS) $(LDFLAGS) $(IDFLAGS) $^ -o $@ $(LIBS)

.PHONY: norm
norm: $(SRCS) $(INCS_DIR)
	@make -C $(FT) norm
	@norminette $^

.PHONY: $(FT)
$(FT):
	@git submodule update --init $@
	@$(MAKE) -C $@

.PHONY: $(READLINE)
$(READLINE):
	@git config http.sslVerify false
	@(cd $@; [ -f Makefile ] || ./configure CFLAGS=-w;)
	@$(MAKE) -C $@

.PHONY: bash
bash:
	@git config http.sslVerify false
	@-git clone https://git.savannah.gnu.org/git/bash.git $@
	@(cd $@; [ -f Makefile ] || ./configure --disable-job-control CFLAGS=-w;)
	@$(MAKE) -C $@

-include $(DEPS)
