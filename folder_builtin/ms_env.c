/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:59:53 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/07 23:00:44 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	envi(t_minishell *singl_mini, t_env_var *env)
{
	t_env_var	*temp;

	if (open_files(singl_mini, env, singl_mini->files))
		return ;
	handle_inout(singl_mini);
	temp = env;
	while (temp)
	{
		if (temp->value != NULL && ft_strncmp(temp->key, "?", 2) != 0
			&& ft_strncmp(temp->key, "PATH", 5) != 0)
		{
			if (ft_strncmp(temp->key, "_", 2) == 0)
				printf("%s=%s\n", temp->key, "/usr/bin/env");
			else
				printf("%s=%s\n", temp->key, temp->value);
		}
		if (ft_strncmp(temp->key, "PATH", 5) == 0 && (get_collector())->p)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
	handle_exit_st(env, singl_mini->nbr_cmd, 0);
}
