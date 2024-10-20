/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tokens_to_minishell.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <bmestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:49:36 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 08:49:38 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_word_new_command(t_minishell_data_help *data, t_token *temp)
{
	char	*temp_args1;

	temp_args1 = ft_strjoin(data->args1, temp->value);
	free(data->args1);
	data->args1 = temp_args1;
	data->command = ft_strdup(temp->value);
	temp_args1 = ft_strjoin(data->args1, "\r");
	free(data->args1);
	data->args1 = temp_args1;
	f_args(data->args);
	data->args = ft_split2(data->args1, "\r");
	return (0);
}

void	token_to_minishell_helper(t_minishell_data_help *data, t_token **temp)
{
	if ((*temp)->type == T_WORD)
	{
		if (data->new_command == 1)
			data->new_command = handle_word_new_command(data, (*temp));
		else
			join_args((*temp), &data->args1, &data->args);
	}
	else if ((*temp)->type == T_REDIRECT_IN)
		(*temp) = add_redirection_in((*temp), &data->files);
	else if ((*temp)->type == T_REDIRECT_OUT)
		(*temp) = add_redirection_out((*temp), &data->files);
	else if ((*temp)->type == T_REDIRECT_APPEND)
		(*temp) = add_redirection_append((*temp), &data->files);
	else if ((*temp)->type == T_HERDOC)
		(*temp) = add_heredoc((*temp), &data->files);
}

void	initialize_token_to_minishell_data(t_minishell_data_help *data)
{
	data->args1 = NULL;
	data->args = NULL;
	data->command = NULL;
	data->files = NULL;
	data->new_command = 1;
}

t_minishell	*token_to_minishell(t_token *tokens)
{
	t_minishell				*minishell;
	t_minishell_data_help	data;
	t_token					*temp;

	initialize_token_to_minishell_data(&data);
	minishell = NULL;
	temp = tokens;
	while (temp)
	{
		if (temp->type == T_PIPE)
		{
			add_minishell_back(&minishell,
				new_minishell(data.command, data.args, data.files));
			data.new_command = init_f(&data);
			temp = temp->next;
			continue ;
		}
		token_to_minishell_helper(&data, &temp);
		temp = temp->next;
	}
	add_minishell_back(&minishell,
		new_minishell(data.command, data.args, data.files));
	return (free(data.args1), minishell);
}
