/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_manage_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:49:10 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 23:43:57 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	t_size(t_token *tokens)
{
	int	size;

	size = 0;
	if (!tokens)
		return (0);
	while (tokens)
	{
		size++;
		tokens = tokens->next;
	}
	return (size);
}

t_token	get_last_token(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	if (!temp)
	{
		temp->type = 0;
		temp->value = NULL;
		temp->next = NULL;
		temp->prev = NULL;
		return (*temp);
	}
	while (temp->next)
		temp = temp->next;
	return (*temp);
}

void	remove_token(t_token **head, t_token *target)
{
	t_token	*temp;
	t_token	*prev;

	if (!*head)
		return ;
	if (*head == target)
	{
		if (target->next)
			target->next->prev = NULL;
		*head = target->next;
		free(target->value);
		free(target);
		return ;
	}
	find_target(head, target, &temp, &prev);
	if (temp)
	{
		if (temp->next)
			temp->next->prev = prev;
		prev->next = temp->next;
		free(temp->value);
		free(temp);
	}
}

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_token_front(t_token **head, t_token *new_token)
{
	new_token->prev = NULL;
	new_token->next = *head;
	*head = new_token;
}
