/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:01:42 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/07 23:01:44 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_init(t_minishell *mini)
{
	int			i;
	int			*pip;
	t_minishell	*temp;

	i = 0;
	pip = malloc(sizeof(int) * 2 * (mini->nbr_cmd - 1));
	while (i < mini->nbr_cmd - 1)
	{
		if (pipe(pip + i * 2))
		{
			perror("pipe");
			f_at_exit();
			exit(1);
		}
		i++;
	}
	temp = mini;
	while (temp)
	{
		temp->pipe = pip;
		temp = temp->next;
	}
}

void	close_pipes(int *pipe, int nbr_cmd)
{
	int	i;

	i = 0;
	while (i < 2 * (nbr_cmd - 1))
		close(pipe[i++]);
}

void	unlink_files(t_minishell *minishell)
{
	while (minishell)
	{
		if (access(minishell->heredoc_path, F_OK) == 0)
		{
			if (unlink(minishell->heredoc_path))
				perror("unlink");
		}
		minishell = minishell->next;
	}
}
