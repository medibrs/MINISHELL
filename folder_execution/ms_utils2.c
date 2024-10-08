/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:01:53 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/09 00:10:51 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	empty_cmd(char *cmd)
{
	if (cmd == NULL)
	{
		f_at_exit();
		exit(0);
	}
	if (ft_strncmp(cmd, "", 1) == 0 || (ft_strlen(cmd) == 2 && cmd[0] == '"'
			&& cmd[1] == '"'))
	{
		write(2, "'': command not found\n", 22);
		return (f_at_exit(), 1);
	}
	if (ft_strncmp(cmd, ".", 2) == 0)
	{
		write(2, "bash: .: filename argument required\n", 36);
		f_at_exit();
		exit(2);
	}
	if (ft_strncmp(cmd, "..", 3) == 0)
	{
		write(2, "..: command not found\n", 22);
		f_at_exit();
		exit(127);
	}
	return (0);
}

void	in_out_ext(t_minishell *singl_mini)
{
	if (singl_mini->infile == 0)
		dup2(singl_mini->pipe[(singl_mini->cmd_order - 1) * 2], 0);
	else
		dup2(singl_mini->infile, 0);
	if (singl_mini->outfile == 1)
		dup2(singl_mini->pipe[singl_mini->cmd_order * 2 + 1], 1);
	else
		dup2(singl_mini->outfile, 1);
}

void	inout_prio(t_minishell *singl_mini)
{
	if (singl_mini->cmd_order == 0)
	{
		dup2(singl_mini->infile, STDIN_FILENO);
		if (singl_mini->outfile == STDOUT_FILENO)
			dup2(singl_mini->pipe[1], STDOUT_FILENO);
		else
			dup2(singl_mini->outfile, 1);
	}
	else if (singl_mini->cmd_order == singl_mini->nbr_cmd - 1)
	{
		if (singl_mini->infile == 0)
			dup2(singl_mini->pipe[(singl_mini->cmd_order - 1) * 2], 0);
		else
			dup2(singl_mini->infile, 0);
		dup2(singl_mini->outfile, 1);
	}
	else
		in_out_ext(singl_mini);
	close_pipes(singl_mini->pipe, singl_mini->nbr_cmd);
}
