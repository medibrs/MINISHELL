/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <bmestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:50:09 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 08:50:12 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_size(int nbr)
{
	int	size;

	size = 0;
	if (nbr < 0)
		nbr = -nbr;
	while (nbr > 9)
	{
		size++;
		nbr = nbr / 10;
	}
	size++;
	return (size);
}

char	*ft_putnbr(int nbr)
{
	char	*to_str;
	int		nbr_size;
	int		ng;

	ng = 0;
	nbr_size = count_size(nbr);
	if (nbr < 0)
	{
		ng = 1;
		nbr = -nbr;
		nbr_size++;
	}
	to_str = malloc(sizeof(char) * (nbr_size + ng + 1));
	to_str[nbr_size--] = '\0';
	while (nbr_size > 0)
	{
		to_str[nbr_size] = (nbr % 10) + '0';
		nbr = nbr / 10;
		nbr_size--;
	}
	to_str[nbr_size] = (nbr % 10) + '0';
	if (ng)
		to_str[0] = '-';
	return (to_str);
}

void	set_exit_code(t_env_var *env, int new_val)
{
	t_env_var	*exit_stat;

	exit_stat = env_bykey(env, "?");
	if (exit_stat)
	{
		if (exit_stat->value)
			free(exit_stat->value);
		exit_stat->value = ft_putnbr(new_val);
	}
}

t_env_var	*c_env(void)
{
	t_env_var	*env;
	char			current_path[1024];

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

void	inc_shlvl(t_env_var *env)
{
	t_env_var	*shlvl;
	char			*new_lvl;
	int				lvl;

	shlvl = env_bykey(env, "SHLVL");
	if (shlvl == NULL || shlvl->value == NULL)
		return ;
	lvl = ft_atoi(shlvl->value);
	lvl++;
	new_lvl = ft_putnbr(lvl);
	free(shlvl->value);
	shlvl->value = new_lvl;
}
