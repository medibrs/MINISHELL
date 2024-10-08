/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <bmestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:47:42 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 08:47:46 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntax_error(const char *str)
{
	if (unclosed_quotes(str) == 1)
		return (puterr("Syntax error : Unclosed quote\n"), 1);
	return (0);
}

int	check_syntax_error_tokens_helper2(t_token *temp)
{
	if (temp->type == T_HERDOC
		&& (temp->next == NULL
			|| temp->next->value[0] == '\0'
			|| temp->next->type != T_WORD))
	{
		if (temp->next == NULL)
			return (3);
		else if (temp->next->value[0] == '\0' || temp->next->type != T_WORD)
			return (9);
	}
	if ((temp->type == T_REDIRECT_IN
			|| temp->type == T_REDIRECT_OUT
			|| temp->type == T_REDIRECT_APPEND
			|| temp->type == T_HERDOC)
		&& temp->next == NULL)
		return (1);
	return (0);
}

int	check_syntax_error_tokens_helper(t_token *temp)
{
	if (check_syntax_error_tokens_helper2(temp) != 0)
		return (check_syntax_error_tokens_helper2(temp));
	if (temp->type == T_PIPE && !temp->next)
		return (2);
	if (temp->type != T_WORD && temp->next->type == T_PIPE)
		return (2);
	if (temp->type == T_REDIRECT_IN && temp->next->type != T_WORD)
		return (5);
	if (temp->type == T_HERDOC && temp->next->type != T_WORD)
		return (4);
	if (temp->type == T_REDIRECT_OUT && temp->next->type != T_WORD)
		return (6);
	if (temp->type == T_REDIRECT_APPEND && temp->next->type != T_WORD)
		return (7);
	if (temp->type == T_PIPE && temp->next->type == T_PIPE)
		return (8);
	return (0);
}

int	check_syntax_error_tokens(t_token *tokens)
{
	t_token	*temp;

	if (!tokens)
		return (0);
	temp = tokens;
	while (temp)
	{
		if (check_syntax_error_tokens_helper(temp) != 0)
			return (check_syntax_error_tokens_helper(temp));
		if (temp->prev == NULL && temp->type == T_PIPE)
			return (2);
		temp = temp->next;
	}
	return (0);
}

int	c_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
