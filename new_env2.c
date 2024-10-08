/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:50:04 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/09 00:19:58 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_size(t_env_var *env)
{
	int			i;
	t_env_var	*temp;

	i = 0;
	temp = env;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

char	**conv_env(t_env_var *env)
{
	char	**env_convert;
	char	*temp;
	int		i;

	i = 0;
	env_convert = NULL;
	env_convert = malloc(sizeof(char *) * (env_size(env) + 1));
	while (env)
	{
		temp = ft_strjoin(env->key, "=");
		env_convert[i] = ft_strjoin(temp, env->value);
		free(temp);
		i++;
		env = env->next;
	}
	env_convert[i] = NULL;
	return (env_convert);
}

t_env_var	*env_get_last(t_env_var *env)
{
	while (env && env->next)
		env = env->next;
	return (env);
}

void	at_end(t_env_var **env, char *target_key)
{
	t_env_var	*target;
	t_env_var	*previuos;
	t_env_var	*last;

	target = env_bykey(*env, target_key);
	previuos = before_target(*env, target);
	last = env_get_last(*env);
	if (target == NULL || target == last || env_size(*env) < 2)
		return ;
	if (target == *env)
		*env = (*env)->next;
	else
		previuos->next = target->next;
	target->next = NULL;
	last->next = target;
}
