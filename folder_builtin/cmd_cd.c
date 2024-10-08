/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:59:30 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/08 23:28:47 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_home(t_env_var *env)
{
	t_env_var	*temp;
	char		*home;

	temp = env_bykey(env, "HOME");
	home = NULL;
	if (temp)
		home = temp->value;
	return (home);
}

int	cd_pars(t_minishell *singl_mini, char *path)
{
	if (path == NULL)
	{
		write(2, "bash: cd: HOME not set\n", 23);
		return (1);
	}
	if (count_arguments(singl_mini->args) > 2)
	{
		write(2, "bash: cd: too many arguments\n", 29);
		return (1);
	}
	if (chdir(path))
	{
		if (errno == 116)
		{
			write(2, "bash: cd: ", ft_strlen("bash: cd: "));
			write(2, path, ft_strlen(path));
			write(2, ": No such file or directory\n", 28);
			return (1);
		}
		write(2, "bash: cd: ", ft_strlen("bash: cd: "));
		perror(path);
		return (1);
	}
	return (0);
}

void	handle_inout(t_minishell *singl_mini)
{
	if (singl_mini->nbr_cmd == 1)
	{
		dup2(singl_mini->infile, 0);
		dup2(singl_mini->outfile, 1);
	}
	else
		inout_prio(singl_mini);
}

void	set_pwd_oldpwd(t_env_var *env, char *new_path)
{
	t_env_var	*oldpwd;
	t_env_var	*pwd;

	oldpwd = env_bykey(env, "OLDPWD");
	pwd = env_bykey(env, "PWD");
	if (oldpwd && pwd)
	{
		free(oldpwd->value);
		oldpwd->value = pwd->value;
		pwd->value = ft_strdup(new_path);
	}
	else if (pwd)
	{
		if (pwd->value)
			free(pwd->value);
		pwd->value = ft_strdup(new_path);
	}
	else if (oldpwd)
	{
		if (oldpwd->value)
			free(oldpwd->value);
		oldpwd->value = NULL;
	}
}

void	cd(t_minishell *singl_mini, t_env_var *env)
{
	char	new_path[1024];
	char	*path;

	if (open_files(singl_mini, env, singl_mini->files))
		return ;
	handle_inout(singl_mini);
	if (count_arguments(singl_mini->args) == 1)
		path = get_home(env);
	else
		path = singl_mini->args[1];
	if (path && ft_strncmp(path, "", 1) == 0
		&& count_arguments(singl_mini->args) <= 2)
		return (handle_exit_st(env, singl_mini->nbr_cmd, 0));
	if (cd_pars(singl_mini, path))
		return (handle_exit_st(env, singl_mini->nbr_cmd, 1));
	if (getcwd(new_path, 1024) == NULL)
	{
		printf("getcwd : %s: %s\n", strerror(errno), path);
		return (handle_exit_st(env, singl_mini->nbr_cmd, 1));
	}
	set_pwd_oldpwd(env, new_path);
	handle_exit_st(env, singl_mini->nbr_cmd, 0);
}
