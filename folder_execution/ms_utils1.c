/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:01:48 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/09 00:11:37 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_cmds(char *command)
{
	if (command && ft_strchr(command, '/') != NULL)
	{
		if (is_directory(command))
		{
			write(2, "bash: ", 6);
			write(2, command, ft_strlen(command));
			write(2, ": Is a directory\n", 17);
			f_at_exit();
			exit(126);
		}
		if (access(command, F_OK) == 0)
			return (1);
		else
		{
			write(2, "bash: ", 6);
			write(2, command, ft_strlen(command));
			write(2, ": ", 2);
			perror("");
			f_at_exit();
			exit(127);
		}
	}
	if (empty_cmd(command))
		exit(127);
	return (0);
}

char	**check_paths(t_env_var *temp, char *cmd)
{
	if (temp == NULL || (temp->value == NULL || ft_strncmp(temp->value, "",
				1) == 0))
	{
		write(2, "bash: ", 6);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": No such file or directory\n",
			ft_strlen(": No such file or directory\n"));
		return (NULL);
	}
	return (ft_split(temp->value, ':'));
}

char	*cmd_path(char *cmd, t_env_var *env, int i)
{
	char	**all_paths;
	char	*path;
	char	*temp;

	if (parse_cmds(cmd))
		return (ft_strdup(cmd));
	all_paths = check_paths(env_bykey(env, "PATH"), cmd);
	if (all_paths == NULL)
		return (NULL);
	while (all_paths && all_paths[i])
	{
		temp = ft_strjoin(all_paths[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, F_OK) == 0)
			return (f_split(all_paths), path);
		free(path);
		i++;
	}
	f_split(all_paths);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", ft_strlen(": command not found\n"));
	return (NULL);
}
