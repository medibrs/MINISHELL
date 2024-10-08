/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:01:19 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/07 23:01:21 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_last_exitstat(t_env_var *env, int status, int *new_line)
{
	if (status == 131 || status == 2)
	{
		if (status == 2)
			status += 128;
		if (status == 131)
			printf("Quit (core dumped)");
		set_exit_code(env, status);
	}
	else
	{
		set_exit_code(env, WEXITSTATUS(status));
	}
	if (status < 200 && status != 0 && *new_line)
	{
		*new_line = 0;
		printf("\n");
	}
}

void	w_child(t_minishell *mini, t_env_var *env,
	int num_cmd, pid_t last_pid)
{
	int		i;
	int		status;
	pid_t	pid;
	int		new_line;

	i = 0;
	new_line = 1;
	close_pipes(mini->pipe, mini->nbr_cmd);
	while (i < num_cmd)
	{
		status = 0;
		pid = wait(&status);
		if (pid == last_pid)
			set_last_exitstat(env, status, &new_line);
		if (status == 2 && pid != last_pid && new_line)
		{
			new_line = 0;
			printf("\n");
		}
		i++;
	}
	unlink_files(mini);
}

void	f_exec(t_minishell *singl_mini, t_env_var **env)
{
	char	**env_conv;

	open_files(singl_mini, *env, singl_mini->files);
	inout_prio(singl_mini);
	if (c_builtin(singl_mini, env) == 0)
	{
		f_at_exit();
		exit(0);
	}
	singl_mini->path = cmd_path(singl_mini->command, *env, 0);
	if (singl_mini->path == NULL)
	{
		f_at_exit();
		exit(127);
	}
	env_conv = conv_env(*env);
	execve(singl_mini->path, singl_mini->args, env_conv);
	perror("bash");
	f_split(env_conv);
	f_at_exit();
	exit(126);
}

void	exec_all(t_minishell *minishell, t_env_var **env)
{
	pid_t		pid;
	t_minishell	*temp;

	pipe_init(minishell);
	temp = minishell;
	handle_sig(SIG_IGN, SIG_IGN, interact_sigint, SIG_IGN);
	while (temp)
	{
		pid = fork();
		if (pid == 0)
		{
			handle_sig(act_sigint, act_sigquit, SIG_IGN, SIG_IGN);
			f_exec(temp, env);
		}
		temp = temp->next;
	}
	w_child(minishell, *env, minishell->nbr_cmd, pid);
	handle_sig(interact_sigint, SIG_IGN, SIG_IGN, SIG_IGN);
}
