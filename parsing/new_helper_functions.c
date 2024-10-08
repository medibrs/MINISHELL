/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_helper_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <bmestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:48:22 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 08:48:24 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	is_pipe(char c)
{
	return (c == '|');
}

int	is_redirection_in(char c)
{
	return (c == '<');
}

int	is_redirection_out(char c)
{
	return (c == '>');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
