/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tokenize_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:49:26 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 23:32:13 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_operator(t_token **head, const char *str, int *i)
{
	if (is_pipe(str[*i]))
		add_token_back(head, new_token(T_PIPE, ft_strdup("|")));
	else if (is_redirection_in(str[*i]))
	{
		if (str[*i + 1] == '<')
		{
			add_token_back(head, new_token(T_HERDOC, ft_strdup("<<")));
			(*i)++;
		}
		else
			add_token_back(head, new_token(T_REDIRECT_IN, ft_strdup("<")));
	}
	else if (is_redirection_out(str[*i]))
	{
		if (str[*i + 1] == '>')
		{
			add_token_back(head, new_token(T_REDIRECT_APPEND, \
				ft_strdup(">>")));
			(*i)++;
		}
		else
			add_token_back(head, new_token(T_REDIRECT_OUT, ft_strdup(">")));
	}
}

void	handle_word(t_token **head, const char *str, int *i)
{
	int		in_quote;
	char	quote;
	char	*temp;
	int		j;

	in_quote = 0;
	j = *i;
	quote = '\0';
	while (str[*i])
	{
		upd_quotes(&in_quote, &quote, str[*i]);
		if (in_quote == 0)
		{
			if (is_operator(str[*i]) || is_whitespace(str[*i]))
				break ;
		}
		(*i)++;
	}
	temp = ft_substr(str, j, *i - j);
	add_token_back(head, new_token(T_WORD, temp));
	(*i)--;
}

t_token	*tokenize_input(const char *str)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_strchr(" \t\n\v\f\r", str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		if (str[i] && ft_strchr("<>|", str[i]))
			handle_operator(&head, str, &i);
		else
			handle_word(&head, str, &i);
		i++;
	}
	return (head);
}
