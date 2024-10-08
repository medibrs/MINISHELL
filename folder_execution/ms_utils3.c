/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 00:10:55 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/09 00:32:08 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_directory(char *cmd)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

void	f_split(char **splited)
{
	int	i;

	i = 0;
	while (splited && splited[i])
		free(splited[i++]);
	if (splited)
		free(splited);
}

int	cmd_count(t_minishell *minishell)
{
	int	count;

	count = 0;
	while (minishell)
	{
		count++;
		minishell = minishell->next;
	}
	return (count);
}
