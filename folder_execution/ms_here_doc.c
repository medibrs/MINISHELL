/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:01:10 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/07 23:01:12 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_delemeter(char *str, char *filename, int fd)
{
	if (str == NULL)
	{
		write(2, "bash: warning: here-document delimited by end-of-file\n",
			ft_strlen(
				"bash: warning: here-document delimited by end-of-file\n"));
		close(fd);
		return (1);
	}
	if (ft_strncmp(filename, str, ft_strlen(str) + 1) == 0)
	{
		free(str);
		close(fd);
		return (1);
	}
	return (0);
}

void	get_fill_heredoc(t_minishell *temp, t_files_redirect *files)
{
	int		fd;
	char	*str;

	fd = open(temp->heredoc_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror("open");
	while (1)
	{
		str = readline(">");
		if (check_delemeter(str, files->filename, fd) == 1)
			break ;
		if (files->should_expand_heredoc == 1 && ft_strchr(str, '$') != NULL)
			str = expand_string(str, 1);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		if (str)
			free(str);
	}
	close(fd);
}

void	loop_heredoc(t_minishell *minishell)
{
	t_files_redirect	*files;
	t_minishell			*temp;

	temp = minishell;
	while (temp)
	{
		files = temp->files;
		while (files)
		{
			if (files->type == T_HERDOC)
				get_fill_heredoc(temp, files);
			files = files->next;
		}
		temp = temp->next;
	}
	f_at_exit();
	exit(0);
}

int	fork_heredoc(t_minishell *minishell, t_env_var *env)
{
	pid_t	pid;
	int		status;

	status = 0;
	handle_sig(SIG_IGN, SIG_IGN, interact_sigint, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		handle_sig(act_sigint, SIG_IGN, SIG_IGN, SIG_IGN);
		loop_heredoc(minishell);
	}
	wait(&status);
	status = status >> 8;
	set_exit_code(env, status);
	handle_sig(interact_sigint, SIG_IGN, SIG_IGN, SIG_IGN);
	return (status);
}

int	c_heredoc(t_minishell *minishell, t_env_var *env, int i)
{
	t_files_redirect	*files;
	t_minishell			*temp;

	temp = minishell;
	while (temp)
	{
		files = temp->files;
		while (files)
		{
			if (files->type == T_HERDOC)
				i++;
			files = files->next;
		}
		temp = temp->next;
	}
	if (i > 0 && i < 17)
		return (fork_heredoc(minishell, env));
	else if (i > 16)
	{
		write(2, "bash: maximum here-document count exceeded\n", 43);
		f_at_exit();
		exit(2);
	}
	return (0);
}
