/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:01:26 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/07 23:01:30 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	s_exec_one(t_minishell *minishell, t_env_var **env)
{
	char	**env_conv;

	open_files(minishell, *env, minishell->files);
	minishell->path = cmd_path(minishell->command, *env, 0);
	if (minishell->path == NULL)
	{
		f_at_exit();
		exit(127);
	}
	dup2(minishell->infile, 0);
	dup2(minishell->outfile, 1);
	env_conv = conv_env(*env);
	execve(minishell->path, minishell->args, env_conv);
	f_split(env_conv);
	f_at_exit();
	perror("execve");
	exit(126);
}

void	exec_one(t_minishell *minishell, t_env_var **env)
{
	pid_t	pid;
	int		status;

	handle_sig(SIG_IGN, SIG_IGN, interact_sigint, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		handle_sig(act_sigint, act_sigquit, SIG_IGN, SIG_IGN);
		s_exec_one(minishell, env);
	}
	wait(&status);
	unlink_files(minishell);
	if (status == 131 || status == 2)
	{
		if (status == 2)
			status += 128;
		if (status == 131)
			printf("Quit (core dumped)");
		set_exit_code(*env, status);
		printf("\n");
	}
	else
		set_exit_code(*env, WEXITSTATUS(status));
	handle_sig(interact_sigint, SIG_IGN, SIG_IGN, SIG_IGN);
}
