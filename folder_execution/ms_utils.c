/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:02:20 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/09 00:12:07 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_arguments(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

int	c_builtin(t_minishell *singl_mini, t_env_var **env)
{
	if (singl_mini->command == NULL)
		return (1);
	if (ft_strncmp("cd", singl_mini->command, 3) == 0)
		return (cd(singl_mini, *env), 0);
	if (ft_strncmp("echo", singl_mini->command, 5) == 0)
		return (echo(singl_mini, *env), 0);
	if (ft_strncmp("env", singl_mini->command, 4) == 0)
		return (envi(singl_mini, *env), 0);
	if (ft_strncmp("pwd", singl_mini->command, 4) == 0)
		return (pwd(singl_mini, *env), 0);
	if (ft_strncmp("export", singl_mini->command, 7) == 0)
		return (export(singl_mini, env), 0);
	if (ft_strncmp("unset", singl_mini->command, 6) == 0)
		return (unset(singl_mini, env), 0);
	if (strncmp("exit", singl_mini->command, 5) == 0)
		return (fake_exit(singl_mini, *env), 0);
	return (1);
}

int	get_is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strncmp("cd", cmd, 3) == 0)
		return (1);
	if (ft_strncmp("echo", cmd, 5) == 0)
		return (1);
	if (ft_strncmp("env", cmd, 4) == 0)
		return (1);
	if (ft_strncmp("pwd", cmd, 4) == 0)
		return (1);
	if (ft_strncmp("export", cmd, 7) == 0)
		return (1);
	if (ft_strncmp("unset", cmd, 6) == 0)
		return (1);
	if (strncmp("exit", cmd, 5) == 0)
		return (1);
	return (0);
}
