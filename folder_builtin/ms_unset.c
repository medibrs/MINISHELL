/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:00:22 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/08 23:29:04 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_var	*before_target(t_env_var *env, t_env_var *target)
{
	t_env_var	*previous;

	previous = NULL;
	while (env)
	{
		if (env == target)
			return (previous);
		previous = env;
		env = env->next;
	}
	return (NULL);
}

void	free_target(t_env_var *target)
{
	if (target->key)
		free(target->key);
	if (target->value)
		free(target->value);
	free(target);
}

int	check_valid_key(t_env_var *target)
{
	if (target == NULL || ft_strncmp(target->key, "_", 2) == 0
		|| ft_strncmp(target->key, "?", 2) == 0)
		return (1);
	return (0);
}

int	verify_files(t_minishell *minishell, t_env_var **env)
{
	if (open_files(minishell, *env, minishell->files))
		return (1);
	handle_inout(minishell);
	return (0);
}

void	unset(t_minishell *minishell, t_env_var **env)
{
	t_env_var	*target;
	t_env_var	*previous;
	int			i;

	if (verify_files(minishell, env))
		return ;
	i = 1;
	while (minishell->args && minishell->args[i])
	{
		target = env_bykey(*env, minishell->args[i++]);
		if (check_valid_key(target))
			continue ;
		else if (target == *env)
		{
			*env = (*env)->next;
			free_target(target);
		}
		else
		{
			previous = before_target(*env, target);
			previous->next = target->next;
			free_target(target);
		}
	}
	handle_exit_st(*env, minishell->nbr_cmd, 0);
}
