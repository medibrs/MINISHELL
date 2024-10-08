/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_free_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <bmestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:48:12 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 08:48:13 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	f_environment(t_env_var *env)
{
	t_env_var	*temp;

	if (!env)
		return ;
	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	f_files(t_files_redirect *files)
{
	t_files_redirect	*temp_files;
	t_files_redirect	*temp_files_next;

	if (files)
	{
		temp_files = files;
		while (temp_files)
		{
			temp_files_next = temp_files->next;
			free(temp_files->filename);
			free(temp_files);
			temp_files = temp_files_next;
		}
	}
}

void	free_minishell(t_minishell *minishell)
{
	t_minishell			*temp;
	char				**temp_args;

	if (!minishell)
		return ;
	if (minishell->pipe)
		free(minishell->pipe);
	while (minishell)
	{
		temp = minishell;
		minishell = minishell->next;
		if (temp->command)
			free(temp->command);
		if (temp->heredoc_path)
			free(temp->heredoc_path);
		if (temp->path)
			free(temp->path);
		if (temp->args)
		{
			temp_args = temp->args;
			f_args(temp_args);
		}
		f_files(temp->files);
		free(temp);
	}
}

void	f_heredocs(t_files_redirect *files)
{
	t_files_redirect	*temp;

	while (files)
	{
		temp = files;
		files = files->next;
		free(temp->filename);
		free(temp);
	}
}

void	f_at_exit(void)
{
	if (*(get_collector())->env)
		f_environment(*(get_collector())->env);
	if (*(get_collector())->minishell)
		free_minishell(*(get_collector())->minishell);
	if (*(get_collector())->tokens)
		f_tokens(*(get_collector())->tokens);
	free((get_collector()));
}
