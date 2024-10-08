/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:59:44 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/07 23:00:47 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(t_minishell *singl_mini, t_env_var *env)
{
	t_env_var	*_pwd;
	char			new_path[1024];

	if (open_files(singl_mini, env, singl_mini->files))
		return ;
	handle_inout(singl_mini);
	_pwd = env_bykey(env, "PWD");
	if (_pwd && _pwd->value)
		printf("%s\n", _pwd->value);
	else
	{
		if (getcwd(new_path, 1024) == NULL)
		{
			perror("getcwd");
			return ;
		}
		printf("%s\n", new_path);
	}
	handle_exit_st(env, singl_mini->nbr_cmd, 0);
}
