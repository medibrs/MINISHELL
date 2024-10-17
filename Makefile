CC = @gcc
NAME = minishell
CFLAGS = -Wall -Werror -Wextra -fPIC -g3 -I/usr/local/opt/readline/include
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline

SRC = main.c \
      folder_builtin/cmd_cd.c \
      folder_builtin/cmd_echo.c \
      folder_builtin/cmd_pwd.c \
      folder_builtin/ms_env.c \
      folder_builtin/ms_exit.c \
      folder_builtin/ms_export_add.c \
      folder_builtin/ms_export_print.c \
      folder_builtin/ms_export.c \
      folder_builtin/ms_unset.c \
      folder_execution/ms_execution.c \
      folder_execution/ms_here_doc.c \
      folder_execution/ms_multiple_cmds.c \
      folder_execution/ms_open_files.c \
      folder_execution/ms_pipe_init.c \
      folder_execution/ms_single_cmd.c \
      folder_execution/ms_utils.c \
      folder_execution/ms_utils1.c \
      folder_execution/ms_utils2.c \
      folder_execution/ms_utils3.c \
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
      new_env4.c \
      signals.c

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a
OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) 
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