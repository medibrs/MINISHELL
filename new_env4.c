/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 00:19:14 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/09 00:39:28 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*c_env(void)
{
	t_env_var	*env;
	char		current_path[1024];

	if (getcwd(current_path, 1024) == NULL)
	{
		perror("getcwd");
		exit(1);
	}
	env = NULL;
	env_add_back(&env, env_node_new(ft_strdup("PATH"), c_paths()));
	env_add_back(&env, env_node_new(ft_strdup("PWD"), ft_strdup(current_path)));
	env_add_back(&env, env_node_new(ft_strdup("SHLVL"), ft_strdup("1")));
	env_add_back(&env, env_node_new(ft_strdup("?"), ft_strdup("0")));
	env_add_back(&env, env_node_new(ft_strdup("OLDPWD"), NULL));
	env_add_back(&env, env_node_new(ft_strdup("_"), ft_strdup("]")));
	(get_collector())->p = 0;
	return (env);
}

char	*c_paths(void)
{
	char	*p;

	p = ft_strdup(
			"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
			);
	return (p);
}

t_env_var	*env_bykey(t_env_var *env, char *key)
{
	t_env_var	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(temp->key) + 1) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
