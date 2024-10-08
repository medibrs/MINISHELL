/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tokens_to_minishell_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <bmestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:49:31 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 08:49:33 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*add_redirection_in(t_token *temp, t_files_redirect **files)
{
	temp = temp->next;
	add_file_redirection_back(files, new_file_redirection(\
		ft_strdup(temp->value), T_REDIRECT_IN));
	return (temp);
}

t_token	*add_redirection_out(t_token *temp, t_files_redirect **files)
{
	temp = temp->next;
	add_file_redirection_back(files, new_file_redirection(\
		ft_strdup(temp->value), T_REDIRECT_OUT));
	return (temp);
}

t_token	*add_redirection_append(t_token *temp, t_files_redirect **files)
{
	temp = temp->next;
	add_file_redirection_back(files, new_file_redirection(\
		ft_strdup(temp->value), T_REDIRECT_APPEND));
	return (temp);
}

t_token	*add_heredoc(t_token *temp, t_files_redirect **files)
{
	temp = temp->next;
	add_file_redirection_back(files, new_file_redirection(\
		ft_strdup(temp->value), T_HERDOC));
	return (temp);
}

int	init_f(t_minishell_data_help *data)
{
	data->command = NULL;
	free(data->args1);
	data->args = NULL;
	data->args1 = NULL;
	data->files = NULL;
	return (1);
}
