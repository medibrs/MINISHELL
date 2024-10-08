/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_helper_functions2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <bmestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:48:26 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 08:48:28 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_env_variable(char c)
{
	return (c == '$');
}

int	is_arithmetic_operator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=');
}

int	is_colone(char c)
{
	return (c == ':');
}

int	is_number(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
