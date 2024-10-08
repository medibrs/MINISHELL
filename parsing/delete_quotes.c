/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <bmestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:47:58 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 08:48:00 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_quotes_from_string_helper(char *str, int *k,
		int *in_single_quote, int *in_double_quote)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '\'' && !*in_double_quote)
			d_quotes1(in_single_quote, str, k, &j);
		else if (str[j] == '\"' && !*in_single_quote)
			d_quotes2(in_double_quote, str, k, &j);
		else if (str[j] == '$' && *in_double_quote == 0 && *in_single_quote == 0
			&& str[j + 1] != '\0' && !is_alpha(str[j + 1]))
		{
			if (str[j] == '\'' && !*in_double_quote)
				*in_single_quote = !*in_single_quote;
			else if (str[j] == '\"' && !*in_single_quote)
				*in_double_quote = !*in_double_quote;
		}
		else
			str[(*k)++] = str[j];
		j++;
	}
}

void	delete_quotes_from_string(char *str)
{
	int	in_single_quote;
	int	in_double_quote;
	int	k;

	k = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	delete_quotes_from_string_helper(str, &k, &in_single_quote,
		&in_double_quote);
	str[k] = '\0';
}

void	delete_quotes_from_files(t_minishell *minishell)
{
	t_minishell			*temp;
	t_files_redirect	*files;

	temp = minishell;
	if (temp != NULL)
	{
		while (temp)
		{
			files = temp->files;
			while (files)
			{
				delete_quotes_from_string(files->filename);
				files = files->next;
			}
			temp = temp->next;
		}
	}
}

void	delete_quotes_from_args(t_minishell *minishell)
{
	t_minishell	*temp;
	int			i;

	i = 0;
	temp = minishell;
	if (temp->args != NULL)
	{
		while (temp && temp->args != NULL)
		{
			i = 0;
			while (temp->args[i])
			{
				delete_quotes_from_string(temp->args[i]);
				i++;
			}
			if (temp->command)
			{
				free(temp->command);
				temp->command = NULL;
			}
			if (temp->args[0])
				temp->command = ft_strdup(temp->args[0]);
			temp = temp->next;
		}
	}
}

t_minishell	*delete_quotes(t_minishell *minishell)
{
	t_minishell			*temp;

	temp = minishell;
	delete_quotes_from_args(temp);
	temp = minishell;
	delete_quotes_from_files(temp);
	return (minishell);
}
