/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:49:44 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/09 00:15:46 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

t_minishell_collecter	*get_collector(void)
{
	static t_minishell_collecter	*lists_collecter = NULL;

	if (lists_collecter == NULL)
	{
		lists_collecter = malloc(sizeof(t_minishell_collecter));
		if (lists_collecter == NULL)
		{
			perror("malloc");
			exit(1);
		}
	}
	return (lists_collecter);
}

int	syntax_checker(t_token *tokens, char *str)
{
	t_files_redirect	*heredocs;
	int					error_code;

	if (tokens == NULL)
		return (f_tokens(tokens), 1);
	if (check_syntax_error(str) != 0)
	{
		set_exit_code(*(get_collector())->env, 2);
		return (1);
	}
	if (check_syntax_error_tokens(tokens) != 0 || tokens == NULL
		|| ft_strlen(str) == 0 || ft_strncmp(str, ":", ft_strlen(str)) == 0)
	{
		heredocs = NULL;
		error_code = check_syntax_error_tokens(tokens);
		c_heredoc_for_syntax_error(&heredocs, tokens, error_code);
		f_heredocs(heredocs);
		set_exit_code(*(get_collector())->env, 2);
		return (1);
	}
	return (0);
}

void	minishell_loop(t_env_var **env, t_token **tokens,
		t_minishell **minishell)
{
	char	*str;

	while (1)
	{
		str = readline("$> ");
		if (str == NULL)
			break ;
		if (str[0] != '\0' && check_whitespaces(str))
			add_history(str);
		*tokens = tokenize_input(str);
		*tokens = expand(*tokens);
		if (check_whitespaces(str) == 0 || syntax_checker(*tokens, str))
		{
			free(str);
			f_tokens(*tokens);
			continue ;
		}
		*minishell = token_to_minishell(*tokens);
		*minishell = delete_quotes(*minishell);
		execution(*minishell, env);
		free(str);
		f_tokens(*tokens);
		free_minishell(*minishell);
	}
}

int	main(int argc, char **argv, char **base_env)
{
	t_env_var		*env;
	t_token			*tokens;
	t_minishell		*minishell;

	(void)argv;
	if (argc > 1)
		return (1);
	init_collecter(&minishell, &env, &tokens);
	get_env_var(&env, base_env);
	handle_sig(interact_sigint, SIG_IGN, SIG_IGN, SIG_IGN);
	minishell_loop(&env, &tokens, &minishell);
	f_environment(env);
	free((get_collector()));
	printf("exit\n");
	return (0);
}
