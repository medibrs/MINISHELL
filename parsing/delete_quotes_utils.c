/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <bmestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:47:54 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 08:47:56 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	d_quotes1(int *in_single_quote, char *str, int *k, int *j)
{
	int	temp_j;

	if (*in_single_quote)
		*in_single_quote = 0;
	else
	{
		*in_single_quote = 1;
		temp_j = (*j) + 1;
		while (str[temp_j] && str[temp_j] != '\'')
			temp_j++;
		if (str[temp_j] == 0)
			str[(*k)++] = str[*j];
	}
}

void	d_quotes2(int *in_double_quote, char *str, int *k, int *j)
{
	int	temp_j;

	if (*in_double_quote)
		*in_double_quote = 0;
	else
	{
		*in_double_quote = 1;
		temp_j = *j + 1;
		while (str[temp_j] && str[temp_j] != '\"')
			temp_j++;
		if (str[temp_j] == 0)
			str[(*k)++] = str[*j];
	}
}

int	check_charset(char *charset, char c)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_dollars(char *str)
{
	if (str[0] == '$' && str[1] == '\0')
		return (1);
	return (0);
}
