/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_export_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:00:06 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/08 23:29:21 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_var	*extr_node(char *arg)
{
	t_env_var	*new;
	char		*equal;
	char		*key;
	char		*value;

	equal = ft_strchr(arg, '=');
	if (equal == NULL)
		new = env_node_new(ft_strdup(arg), NULL);
	else
	{
		key = ft_substr(arg, 0, equal - arg);
		value = ft_substr(equal + 1, 0, ft_strlen(arg));
		new = env_node_new(key, value);
	}
	return (new);
}

void	parse_error(char *arg)
{
	write(2, "bash: export: ", ft_strlen("bash: export: "));
	write(2, arg, ft_strlen(arg));
	write(2, ": not a valid identifier\n",
		ft_strlen(": not a valid identifier\n"));
}

int	parse_node(t_env_var *new, char *arg)
{
	int	i;
	int	plus;

	i = 0;
	plus = 0;
	while (new && new->key && new->key[i])
	{
		if ((new->key[i] < 'a' || new->key[i] > 'z') && (new->key[i] < 'A'
				|| new->key[i] > 'Z') && (new->key[i] < '0'
				|| new->key[i] > '9') && new->key[i] != '_'
			&& new->key[i] != '+')
			return (parse_error(arg), 1);
		if (new->key[i] == '+')
			plus++;
		if (plus > 1 || new->key[0] == '+' || (new->key[0] >= '0'
				&& new->key[0] <= '9'))
			return (parse_error(arg), 1);
		i++;
	}
	if ((new->key && new->key[0] == '\0') || (new->key[ft_strlen(new->key)
				- 1] == '+' && new->value == NULL) || (plus == 1
			&& new->key[ft_strlen(new->key) - 1] != '+'))
		return (parse_error(arg), 1);
	return (0);
}

void	app_value(t_env_var *env, t_env_var *new)
{
	t_env_var	*target;
	t_env_var	*temp;
	t_env_var	*previous;
	char		*helper;

	new->key[ft_strlen(new->key) - 1] = '\0';
	if (ft_strncmp(new->key, "PATH", 5) == 0)
		(get_collector())->p = 1;
	target = env_bykey(env, new->key);
	temp = env->next->next;
	previous = env->next;
	if (target == NULL)
	{
		previous->next = new;
		new->next = temp;
	}
	else if (new->value != NULL)
	{
		helper = ft_strjoin(target->value, new->value);
		free(target->value);
		target->value = helper;
		f_environment(new);
	}
	else
		f_environment(new);
}

void	rep_value(t_env_var *env, t_env_var *new)
{
	t_env_var	*target;
	t_env_var	*temp;
	t_env_var	*previous;

	target = env_bykey(env, new->key);
	temp = env;
	previous = (env)->next;
	if (ft_strncmp(new->key, "PATH", 5) == 0)
		(get_collector())->p = 1;
	if (target == NULL)
	{
		temp = temp->next->next;
		previous->next = new;
		new->next = temp;
	}
	else if (new->value != NULL)
	{
		free(target->value);
		target->value = ft_strdup(new->value);
		f_environment(new);
	}
	else
		f_environment(new);
}
