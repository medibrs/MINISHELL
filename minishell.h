/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:06:13 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/08 23:44:01 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_REDIRECT_APPEND,
	T_HERDOC
}								t_token_type;

typedef struct s_env_var
{
	char						*key;
	char						*value;
	struct s_env_var			*next;
}								t_env_var;

typedef struct s_files_redirect
{
	char						*filename;
	int							should_expand_heredoc;
	t_token_type				type;
	struct s_files_redirect		*next;
}								t_files_redirect;

typedef struct s_token
{
	t_token_type				type;
	char						*value;
	struct s_token				*next;
	struct s_token				*prev;
}								t_token;

typedef struct s_cmd_args
{
	char						*args;
	struct s_cmd_args			*next;
}								t_cmd_args;

typedef struct s_cmd_minishell
{
	char						*command;
	char						**args;
	char						*path;
	int							infile;
	int							outfile;
	int							cmd_order;
	int							nbr_cmd;
	int							*pipe;
	char						*heredoc_path;
	t_files_redirect			*files;
	struct s_cmd_minishell		*next;
}								t_minishell;

typedef struct s_minishell_data_help
{
	char						*command;
	char						*args1;
	char						**args;
	t_files_redirect			*files;
	int							new_command;
}								t_minishell_data_help;

typedef struct s_minishell_collecter
{
	t_minishell					**minishell;
	t_token						**tokens;
	t_env_var					**env;
	int							p;
}								t_minishell_collecter;

t_minishell_collecter			*get_collector(void);

void							set_exit_code(t_env_var *env, int new_val);
int								count_arguments(char **args);
int								empty_cmd(char *cmd);
char							*ft_putnbr(int nbr);
void							swap_data(t_env_var *helper);
void							sort_env(t_env_var **sort_env);
void							print(char *key, char *value);
void							handle_heredoc_signals(int signal);
char							*expand_string(char *str, int from_heredoc);
int								is_directory(char *cmd);
int								parse_cmds(char *command);
char							**check_paths(t_env_var *temp, char *cmd);

void							interact_sigint(int sig);
void							interact_sigquit(int sig);
void							act_sigint(int sig);
void							act_sigquit(int sig);
void							handle_sig(void (*sigint)(int),
									void (*sigquit)(int),
									void (*sigint_old)(int),
									void (*sigquit_old)(int));

t_env_var						*env_node_new(char *key, char *value);
void							env_add_back(t_env_var **env,
									t_env_var *node);
int								env_size(t_env_var *env);
t_env_var						*before_target(t_env_var *env,
									t_env_var *target);
void							at_end(t_env_var **env,
									char *target_key);
void							inc_shlvl(t_env_var *env);
char							*c_paths(void);
t_env_var						*c_env(void);
void							get_env_var(t_env_var **env, char **base_env);
t_env_var						*env_bykey(t_env_var *env, char *key);
char							**conv_env(t_env_var *env);

t_env_var						*dup_env(t_env_var *env);
t_env_var						*extr_node(char *arg);
int								parse_node(t_env_var *new, char *arg);
void							app_value(t_env_var *env,
									t_env_var *new);
void							rep_value(t_env_var *env,
									t_env_var *new);

char							*cmd_path(char *cmd, t_env_var *env,
									int i);
int								cmd_count(t_minishell *mini);
void							inout_prio(t_minishell *singl_mini);
void							unlink_files(t_minishell *minishell);

int								c_builtin(t_minishell *singl_mini,
									t_env_var **env);
int								get_is_builtin(char *cmd);

int								check_delemeter(char *str, char *filename,
									int fd);
void							get_fill_heredoc(t_minishell *temp,
									t_files_redirect *files);
void							loop_heredoc(t_minishell *minishell);
int								fork_heredoc(t_minishell *minishell,
									t_env_var *env);
int								c_heredoc(t_minishell *minishell,
									t_env_var *env, int i);

int								file_error(t_minishell *minishell,
									t_env_var *env, char *filename);
int								file_ext(t_minishell *minishell,
									t_env_var *env,
									t_files_redirect *files);
int								open_files(t_minishell *minishell,
									t_env_var *env,
									t_files_redirect *files);
void							s_exec_one(t_minishell *minishell,
									t_env_var **env);
void							exec_one(t_minishell *minishell,
									t_env_var **env);

void							pipe_init(t_minishell *mini);
void							close_pipes(int *pipe, int nbr_cmd);
void							unlink_files(t_minishell *minishell);

void							w_child(t_minishell *mini,
									t_env_var *env, int num_cmd, pid_t pid);
void							in_out_ext(t_minishell *singl_mini);
void							inout_prio(t_minishell *singl_mini);
void							f_exec(t_minishell *singl_mini,
									t_env_var **env);
void							exec_all(t_minishell *minishell,
									t_env_var **env);

void							rest_std_inout(int stdout, int stdin);
char							*herdoc_path(int i);
void							minishell_init(t_minishell *minishell,
									int count_cmds);
void							under_score(t_minishell *minishell,
									t_env_var **env);
void							execution(t_minishell *minishell,
									t_env_var **env);

void							add_node(t_env_var *env,
									t_env_var *new);
int								export_print(t_env_var **env);
int								export_add(t_minishell *minishell,
									t_env_var *env);
void							handle_inout(t_minishell *singl_mini);
void							handle_exit_st(t_env_var *env,
									int nbr_cmd, int exit_value);
void							cd(t_minishell *singl_mini, t_env_var *env);
void							envi(t_minishell *singl_mini,
									t_env_var *env);
void							fake_exit(t_minishell *singl_mini,
									t_env_var *env);
void							pwd(t_minishell *singl_mini,
									t_env_var *env);
void							unset(t_minishell *minishell,
									t_env_var **env);
void							export(t_minishell *minishell,
									t_env_var **env);
void							echo(t_minishell *single_mini,
									t_env_var *env);
void							check_quote(const char *str,
									int *in_single_quotes,
									int *in_double_quotes, int *i);
void							upd_quotes(int *in_quote, char *quote,
									char c);
int								check_quotes(char *str);
int								unclosed_quotes(const char *str);
void							nb_quote(char c, int *nb_quote_single,
									int *nb_quote_double);
void							ins_token(t_token **head, t_token *new_token,
									t_token *target);
void							add_token_back(t_token **head,
									t_token *new_token);
char							*get_type_token(t_token_type type);
void							print_tokens(t_token *tokens);
int								t_size(t_token *tokens);
t_token							get_last_token(t_token *tokens);
void							remove_token(t_token **head, t_token *target);
t_token							*new_token(t_token_type type, char *value);
void							add_token_front(t_token **head,
									t_token *new_token);
void							find_target(t_token **head, t_token *target,
									t_token **temp, t_token **prev);
int								is_operator(char c);
int								is_pipe(char c);
int								is_redirection_in(char c);
int								is_redirection_out(char c);
int								is_quote(char c);
int								is_env_variable(char c);
int								is_arithmetic_operator(char c);
int								is_colone(char c);
int								is_number(char c);
int								is_alpha(char c);
t_files_redirect				*new_file_redirection(char *filename,
									t_token_type type);
void							add_file_redirection_back(
									t_files_redirect **head,
									t_files_redirect *new_file);
void							print_files(t_minishell *temp);
void							handle_operator(t_token **head, const char *str,
									int *i);
void							handle_word(t_token **head, const char *str,
									int *i);
t_token							*tokenize_input(const char *str);
int								is_whitespace(char c);
int								check_syntax_error(const char *str);
void							puterr(char *str);
int								check_syntax_error_tokens_helper2(
									t_token *temp);
int								check_syntax_error_tokens_helper(t_token *temp);
int								check_syntax_error_tokens(t_token *tokens);
int								s_minishell_size(t_minishell *minishell);
t_minishell						*new_minishell(char *command, char **args,
									t_files_redirect *files);
void							add_minishell_back(t_minishell **head,
									t_minishell *new_minishell);
void							print_minishell(t_minishell *minishell);
void							*new_arg(char *arg);
void							add_arg_back(t_cmd_args **head,
									t_cmd_args *new_arg);
int								count_cmd_args(char **args);
void							join_args(t_token *temp, char **args1,
									char ***args);
void							print_cmd_args(t_minishell *temp);

int								check_charset(char *charset, char c);
void							initialize_value_split2(int *j, char *quote,
									int *in_quote);
void							ft_skip2(int *i, int in_quote, const char *s,
									char *charset);
char							**ft_split2_helper(char **res, char const *s,
									char *charset, int i);
char							**ft_split2(char const *s, char *charset);
int								ft_count_words(char const *str, char *charset);
void							init_expand_string(int *i,
									int *in_single_quotes,
									int *in_double_quotes, char **env_variable);
char							*expand_string(char *str, int from_heredoc);
void							split_expanded_string(t_token **temp,
									t_token **tokens);
int								expand_string_helper(t_token **tokens,
									t_token **temp);
int								is_word(char c);
void							find_target(t_token **head, t_token *target,
									t_token **temp, t_token **prev);
int								check_whitespaces(const char *str);
void							handle_quotes_after_dollar(char *str);
char							*change_value(char *str, int *i, int *index,
									char *env_variable);
int								expand_helper(int index, int *i, char *str);
int								ambiguouse_redirect(char *old);
int								ft_remove_char(char *str, int index);
void							delete_quotes_from_string(char *str);
t_token							*expand(t_token *tokens);
void							delete_quotes_from_files(
									t_minishell *minishell);
void							delete_quotes_from_args(t_minishell *minishell);
t_minishell						*delete_quotes(t_minishell *minishell);
int								in_quote(const char *str);
t_token							*add_redirection_in(t_token *temp,
									t_files_redirect **files);
t_token							*add_redirection_out(t_token *temp,
									t_files_redirect **files);
t_token							*add_redirection_append(t_token *temp,
									t_files_redirect **files);
t_token							*add_heredoc(t_token *temp,
									t_files_redirect **files);
int								init_f(
									t_minishell_data_help *data);
int								handle_word_new_command(
									t_minishell_data_help *data,
									t_token *temp);
void							token_to_minishell_helper(
									t_minishell_data_help *data,
									t_token **temp);
void							initialize_token_to_minishell_data(
									t_minishell_data_help *data);
t_minishell						*token_to_minishell(t_token *tokens);
int								is_empty(char *str);
void							h_ctrl_c(int signal);
int								c_space(const char *str);
void							h_sigquit(int signal);
int								check_delemeter_for_sr(char *str,
									char *filename);
void							get_fill_heredoc_for_sr(
									t_files_redirect *heredoc);
void							loop_heredoc_for_sr(
									t_files_redirect *heredocs);
void							fill_error_codes(char **error_codes);
int								heredoc_sr_help(int *heredoc_counter,
									t_token *tokens, int error_code,
									t_files_redirect **heredocs);
int								c_heredoc_for_syntax_error(
									t_files_redirect **heredocs,
									t_token *tokens, int error_code);
void							print_heredocs(t_files_redirect *files);
void							init_collecter(t_minishell **minishell,
									t_env_var **env, t_token **tokens);
int								not_alnum(char c);
void							d_quotes1(int *in_single_quote,
									char *str, int *k, int *j);
void							d_quotes2(int *in_double_quote,
									char *str, int *k, int *j);
int								check_charset(char *charset, char c);
int								check_dollars(char *str);

void							f_at_exit(void);
void							f_heredocs(t_files_redirect *files);
void							free_minishell(t_minishell *minishell);
void							f_files(t_files_redirect *files);
void							f_environment(t_env_var *env);
void							f_args(char **args);
char							**ft_free(char **strs);
void							f_tokens(t_token *tokens);
void							f_split(char **splited);
void							f_at_exit(void);
void							f_environment(t_env_var *env);
void							f_copy(t_env_var *env);
#endif
