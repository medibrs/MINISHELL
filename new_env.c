/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <bmestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:49:59 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 08:50:02 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*env_node_new(char *key, char *value)
{
	t_env_var	*new;

	new = malloc(sizeof(t_env_var));
	if (new == NULL)
		exit(1);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env_var **env, t_env_var *node)
{
	t_env_var	*temp;

	temp = NULL;
	if (*env == NULL)
		*env = node;
	else
	{
		temp = *env;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
}

void	add_exit_status(t_env_var **env)
{
	t_env_var	*exit_stat;

	exit_stat = NULL;
	exit_stat = env_bykey(*env, "?");
	if (exit_stat)
		return ;
	env_add_back(env, env_node_new(ft_strdup("?"), ft_strdup("0")));
}

void	get_env_var(t_env_var **env, char **base_env)
{
	int		i;
	char	*equal;
	char	*key;
	char	*value;

	i = 0;
	if (base_env == NULL || base_env[0] == NULL)
	{
		*env = c_env();
		return ;
	}
	while (base_env[i])
	{
		equal = ft_strchr(base_env[i], '=');
		key = ft_substr(base_env[i], 0, equal - base_env[i]);
		value = ft_substr(equal + 1, 0, ft_strlen(base_env[i]));
		env_add_back(env, env_node_new(key, value));
		i++;
	}
	add_exit_status(env);
	inc_shlvl(*env);
	at_end(env, "OLDPWD");
	at_end(env, "_");
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
