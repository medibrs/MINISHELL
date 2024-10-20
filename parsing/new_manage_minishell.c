/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_manage_minishell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <bmestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:49:00 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 08:49:02 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	s_minishell_size(t_minishell *minishell)
{
	int	size;

	size = 0;
	if (!minishell)
		return (0);
	while (minishell)
	{
		size++;
		minishell = minishell->next;
	}
	return (size);
}

t_minishell	*new_minishell(char *command, char **args,
	t_files_redirect *files)
{
	t_minishell	*minishell;

	minishell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!minishell)
	{
		free(command);
		free(args);
		return (NULL);
	}
	minishell->heredoc_path = NULL;
	minishell->infile = 0;
	minishell->outfile = 0;
	minishell->pipe = 0;
	minishell->path = NULL;
	minishell->command = command;
	minishell->args = args;
	minishell->files = files;
	minishell->next = NULL;
	return (minishell);
}

void	add_minishell_back(t_minishell **head, t_minishell *new_minishell)
{
	t_minishell	*temp;

	if (!*head)
		*head = new_minishell;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_minishell;
	}
}

void	print_minishell(t_minishell *minishell)
{
	t_minishell			*temp;
	int					i;

	i = 0;
	temp = minishell;
	while (temp)
	{
		printf("--------------------\n");
		if (temp->command)
			printf("command [%d]: [%s]\n", i, temp->command);
		print_cmd_args(temp);
		print_files(temp);
		printf("--------------------\n");
		temp = temp->next;
		i++;
	}
}
