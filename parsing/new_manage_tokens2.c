/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_manage_tokens2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:49:16 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 23:43:57 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ins_token(t_token **head, t_token *new_token, t_token *target)
{
	t_token	*temp;

	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next && temp->next != target)
			temp = temp->next;
		new_token->next = temp->next;
		if (temp->next)
			temp->next->prev = new_token;
		new_token->prev = temp;
		temp->next = new_token;
	}
}

void	add_token_back(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
		new_token->prev = temp;
	}
}

char	*get_type_token(t_token_type type)
{
	if (type == T_WORD)
		return ("T_WORD");
	else if (type == T_PIPE)
		return ("T_PIPE");
	else if (type == T_REDIRECT_IN)
		return ("T_REDIRECT_IN");
	else if (type == T_REDIRECT_OUT)
		return ("T_REDIRECT_OUT");
	else if (type == T_REDIRECT_APPEND)
		return ("T_REDIRECT_APPEND");
	else if (type == T_HERDOC)
		return ("T_HERDOC");
	return ("UNKNOWN");
}

void	print_tokens(t_token *tokens)
{
	printf("--------------------\n");
	while (tokens)
	{
		printf("type: %s, value: [%s]\n", \
			get_type_token(tokens->type), tokens->value);
		tokens = tokens->next;
	}
	printf("--------------------\n");
}
