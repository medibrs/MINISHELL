/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:59:59 by mbouras           #+#    #+#             */
/*   Updated: 2024/10/07 23:00:41 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_digits(char *str)
{
	int	i;

	i = 0;
	if (str && (str[i] == '-' || str[i] == '+'))
		i++;
	if (str && str[i] == '\0')
		return (0);
	while (str && str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	print_error(char *arg, int flag)
{
	if (flag == 0)
	{
		write(2, "bash: exit: ", ft_strlen("bash: exit: "));
		write(2, arg, ft_strlen(arg));
		write(2, ": numeric argument required\n",
			ft_strlen(": numeric argument required\n"));
		f_at_exit();
		exit(2);
	}
	if (flag == 1)
	{
		write(2, "bash: exit: too many arguments\n",
			ft_strlen("bash: exit: too many arguments\n"));
	}
}

void	fake_exit(t_minishell *singl_mini, t_env_var *env)
{
	int	exit_status;

	if (open_files(singl_mini, env, singl_mini->files))
		return ;
	handle_inout(singl_mini);
	exit_status = ft_atoi((env_bykey(env, "?")->value));
	if (singl_mini->nbr_cmd == 1)
		printf("exit\n");
	if (singl_mini->args && singl_mini->args[1])
	{
		if (check_digits(singl_mini->args[1]) == 0)
			print_error(singl_mini->args[1], 0);
		if (singl_mini->args[2] != NULL)
		{
			set_exit_code(env, 1);
			return (print_error(singl_mini->args[1], 1), (void)0);
		}
		exit_status = ft_atoi(singl_mini->args[1]);
	}
	f_at_exit();
	exit(exit_status);
}
