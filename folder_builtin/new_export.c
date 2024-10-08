/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:00:17 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/07 23:00:31 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_node(t_env_var *env, t_env_var *new)
{
	if (strchr(new->key, '+'))
		app_value(env, new);
	else
		rep_value(env, new);
}

int	export_print(t_env_var **env)
{
	t_env_var	*copy_env;
	t_env_var	*helper;

	copy_env = dup_env(*env);
	sort_env(&copy_env);
	helper = copy_env;
	while (helper)
	{
		if (strncmp(helper->key, "_", 2) != 0 && ft_strncmp(helper->key, "?",
				2) != 0 && ft_strncmp(helper->key, "PATH", 2) != 0)
			print(helper->key, helper->value);
		if (ft_strncmp(helper->key, "PATH", 2) == 0
			&& (get_collector())->p)
			print(helper->key, helper->value);
		helper = helper->next;
	}
	f_copy(copy_env);
	return (0);
}

int	export_add(t_minishell *minishell, t_env_var *env)
{
	t_env_var	*new;
	int				i;
	int				exit_value;

	i = 1;
	new = NULL;
	exit_value = 0;
	while (minishell->args && minishell->args[0] && minishell->args[i])
	{
		new = extr_node(minishell->args[i]);
		if (parse_node(new, minishell->args[i]))
		{
			f_environment(new);
			if (minishell->nbr_cmd == 1)
				exit_value = 1;
			i++;
			continue ;
		}
		add_node(env, new);
		i++;
	}
	return (exit_value);
}

void	handle_exit_st(t_env_var *env, int nbr_cmd, int exit_value)
{
	if (nbr_cmd == 1)
		set_exit_code(env, exit_value);
	else
	{
		f_at_exit();
		exit(exit_value);
	}
}

void	export(t_minishell *minishell, t_env_var **env)
{
	int	exit_value;

	if (open_files(minishell, *env, minishell->files))
		return ;
	handle_inout(minishell);
	if (count_arguments(minishell->args) < 2)
		exit_value = export_print(env);
	else
		exit_value = export_add(minishell, *env);
	handle_exit_st(*env, minishell->nbr_cmd, exit_value);
}
