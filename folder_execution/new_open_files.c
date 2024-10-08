/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:01:34 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/07 23:01:35 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	file_error(t_minishell *minishell, t_env_var *env, char *filename)
{
	write(2, "bash: ", 6);
	write(2, filename, ft_strlen(filename));
	write(2, ": ", 2);
	perror("");
	if (minishell->nbr_cmd == 1 && get_is_builtin(minishell->command))
	{
		set_exit_code(env, 1);
		return (1);
	}
	set_exit_code(env, 1);
	f_at_exit();
	exit(1);
}

int	check_std_in_out(e_token_type type, char *filename)
{
	if (ft_strncmp(filename, "/dev/stdout", ft_strlen(filename) + 1) == 0
		&& (type == T_REDIRECT_OUT || type == T_REDIRECT_APPEND))
		return (2);
	if (ft_strncmp(filename, "/dev/stdin", ft_strlen(filename) + 1) == 0
		&& type == T_REDIRECT_IN)
		return (2);
	return (0);
}

int	file_ext_2(t_minishell *minishell, t_env_var *env,
		t_files_redirect *files)
{
	if (check_std_in_out(files->type, files->filename))
		return (2);
	if (files->type == T_REDIRECT_APPEND)
	{
		if (minishell->outfile != 1)
			close(minishell->outfile);
		minishell->outfile = open(files->filename,
				O_WRONLY | O_APPEND | O_CREAT, 0664);
		if (minishell->outfile < 0)
			return (file_error(minishell, env, files->filename));
	}
	else if (files->type == T_HERDOC)
	{
		if (minishell->infile != 0)
			close(minishell->infile);
		minishell->infile = open(minishell->heredoc_path, O_RDONLY, 0644);
		if (minishell->infile < 0)
			return (file_error(minishell, env, minishell->heredoc_path));
	}
	return (0);
}

int	file_ext(t_minishell *minishell, t_env_var *env,
		t_files_redirect *files)
{
	if (check_std_in_out(files->type, files->filename))
		return (2);
	if (files->type == T_REDIRECT_IN)
	{
		if (minishell->infile != 0)
			close(minishell->infile);
		minishell->infile = open(files->filename, O_RDONLY, 0644);
		if (minishell->infile < 0)
			return (file_error(minishell, env, files->filename));
	}
	else if (files->type == T_REDIRECT_OUT)
	{
		if (minishell->outfile != 1)
			close(minishell->outfile);
		minishell->outfile = open(files->filename, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (minishell->outfile < 0)
			return (file_error(minishell, env, files->filename));
	}
	return (0);
}

int	open_files(t_minishell *minishell, t_env_var *env,
		t_files_redirect *files)
{
	int	return_value;

	files = minishell->files;
	while (files)
	{
		return_value = file_ext(minishell, env, files);
		if (return_value == 1)
			return (1);
		else if (return_value == 0)
		{
			return_value = file_ext_2(minishell, env, files);
			if (return_value == 1)
				return (1);
		}
		files = files->next;
	}
	return (0);
}
