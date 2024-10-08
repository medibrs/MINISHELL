CC = @gcc
NAME = minishell
CFLAGS = -Wall -Werror -Wextra -fPIC -g3 -I/usr/local/opt/readline/include
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline

SRC = main.c \
      folder_builtin/new_cmd_cd.c \
      folder_builtin/new_cmd_echo.c \
      folder_builtin/new_cmd_pwd.c \
      folder_builtin/new_env.c \
      folder_builtin/new_exit.c \
      folder_builtin/new_export_add.c \
      folder_builtin/new_export_print.c \
      folder_builtin/new_export.c \
      folder_builtin/new_unset.c \
      folder_execution/new_execution.c \
      folder_execution/new_here_doc.c \
      folder_execution/new_multiple_cmds.c \
      folder_execution/new_open_files.c \
      folder_execution/new_pipe_init.c \
      folder_execution/new_single_cmd.c \
      folder_execution/new_utils.c \
      folder_execution/new_utils1.c \
      folder_execution/new_utils2.c \
      parsing/check_syntax_error.c \
      parsing/check_syntax_error2.c \
      parsing/delete_quotes_utils.c \
      parsing/delete_quotes.c \
      parsing/expand_utils.c \
      parsing/expand.c \
      parsing/new_free_data.c \
      parsing/new_free_data2.c \
      parsing/new_helper_functions.c \
      parsing/new_helper_functions2.c \
      parsing/new_helper_functions3.c \
      parsing/new_helper_functions4.c \
      parsing/new_helper_functions5.c \
      parsing/new_manage_args.c \
      parsing/new_manage_files_redirections.c \
      parsing/new_manage_minishell.c \
      parsing/new_manage_quotes.c \
      parsing/new_manage_tokens.c \
      parsing/new_manage_tokens2.c \
      parsing/new_split_minishell.c \
      parsing/new_tokenize_input.c \
      parsing/new_tokens_to_minishell_utils.c \
      parsing/new_tokens_to_minishell.c \
      new_env.c \
      new_env2.c \
      new_env3.c \
      signals.c

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a
OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) -lreadline -lhistory
	@echo "compiled"

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@make bonus -C $(LIBFT_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJ)
	@echo "cleaned"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "fcleaned"

re: fclean all

.SECONDARY: $(OBJ)