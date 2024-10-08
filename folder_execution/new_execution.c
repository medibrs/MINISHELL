/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:01:04 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/08 23:27:19 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rest_std_inout(int stdout, int stdin)
{
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	close(stdin);
	close(stdout);
}

char	*herdoc_path(int i)
{
	char	*heredoc_path;

	heredoc_path = malloc(sizeof(char) * (ft_strlen("/tmp/herdoc_buffer_")
				+ 2));
	ft_strlcpy(heredoc_path, "/tmp/herdoc_buffer_", 19);
	heredoc_path[ft_strlen("/tmp/herdoc_buffer_")] = i + 'a';
	heredoc_path[ft_strlen("/tmp/herdoc_buffer_") + 1] = '\0';
	return (heredoc_path);
}

void	minishell_init(t_minishell *minishell, int count_cmds)
{
	int			i;
	t_minishell	*temp;

	i = 0;
	temp = minishell;
	while (temp)
	{
		temp->cmd_order = i;
		temp->path = NULL;
		temp->pipe = NULL;
		temp->infile = 0;
		temp->outfile = 1;
		temp->nbr_cmd = count_cmds;
		temp->heredoc_path = herdoc_path(i);
		i++;
		temp = temp->next;
	}
}

void	under_score(t_minishell *minishell, t_env_var **env)
{
	t_env_var	*env_under_score;

	env_under_score = env_bykey(*env, "_");
	if (env_under_score)
	{
		if (count_arguments(minishell->args) > 0)
		{
			free(env_under_score->value);
			env_under_score->value
				= ft_strdup(
					minishell->args[count_arguments(minishell->args) - 1]);
		}
		else
		{
			free(env_under_score->value);
			env_under_score->value = ft_strdup("");
		}
	}
}

void	execution(t_minishell *minishell, t_env_var **env)
{
	int	stdout;
	int	stdin;

	stdout = dup(STDOUT_FILENO);
	stdin = dup(STDIN_FILENO);
	minishell_init(minishell, cmd_count(minishell));
	if (c_heredoc(minishell, *env, 0))
		return ;
	if (cmd_count(minishell) == 1)
	{
		if (c_builtin(minishell, env) == 0)
		{
			under_score(minishell, env);
			rest_std_inout(stdout, stdin);
			return ;
		}
		else
			exec_one(minishell, env);
		under_score(minishell, env);
	}
	else
		exec_all(minishell, env);
	rest_std_inout(stdout, stdin);
}
