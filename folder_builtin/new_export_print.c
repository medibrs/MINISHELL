/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:00:12 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/07 23:00:34 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_data(t_env_var *helper)
{
	char	*key_temp;
	char	*value_temp;

	key_temp = helper->key;
	helper->key = helper->next->key;
	helper->next->key = key_temp;
	value_temp = helper->value;
	helper->value = helper->next->value;
	helper->next->value = value_temp;
}

void	sort_env(t_env_var **sort_env)
{
	int				b;
	t_env_var	*helper;

	b = 1;
	while (b)
	{
		b = 0;
		helper = *sort_env;
		while (helper && helper->next)
		{
			if (strncmp(helper->key, helper->next->key, ft_strlen(helper->key)
					+ 1) > 0)
			{
				swap_data(helper);
				b = 1;
			}
			helper = helper->next;
		}
	}
}

t_env_var	*dup_env(t_env_var *env)
{
	t_env_var	*copy;

	copy = NULL;
	while (env)
	{
		if (env->value == NULL)
			env_add_back(&copy, env_node_new(ft_strdup(env->key), NULL));
		else
			env_add_back(&copy, env_node_new(ft_strdup(env->key),
					ft_strdup(env->value)));
		env = env->next;
	}
	return (copy);
}

void	f_copy(t_env_var *env)
{
	t_env_var	*temp;

	temp = env;
	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	print(char *key, char *value)
{
	if (value != NULL)
		printf("declare -x %s=\"%s\"\n", key, value);
	else
		printf("declare -x %s\n", key);
}
