/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_manage_files_redirections.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:48:53 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 23:43:57 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_files_redirect	*new_file_redirection(char *filename, t_token_type type)
{
	t_files_redirect	*file;

	file = (t_files_redirect *)malloc(sizeof(t_files_redirect));
	if (!file)
		return (NULL);
	file->filename = filename;
	file->should_expand_heredoc = 1;
	file->should_expand_heredoc = check_quotes(filename);
	file->type = type;
	file->next = NULL;
	return (file);
}

void	add_file_redirection_back(t_files_redirect **head
	, t_files_redirect *new_file)
{
	t_files_redirect	*temp;

	if (!*head)
		*head = new_file;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_file;
	}
}

void	print_files(t_minishell *temp)
{
	t_files_redirect	*temp_files;

	if (temp->files)
	{
		temp_files = temp->files;
		printf("files :\n");
		while (temp_files)
		{
			printf(" file: [%s] \n", temp_files->filename);
			printf("  type: %s \n", get_type_token(temp_files->type));
			temp_files = temp_files->next;
		}
		printf("\n");
	}
}
