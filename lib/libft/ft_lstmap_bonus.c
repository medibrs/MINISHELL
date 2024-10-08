/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 08:25:13 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/20 19:02:36 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newl;
	t_list	*elem;
	void	*newc;

	newl = NULL;
	while (lst && f && del)
	{
		newc = f(lst ->content);
		elem = ft_lstnew(newc);
		if (elem == NULL)
		{
			ft_lstclear(&newl, del);
			free(newc);
			return (NULL);
		}
		ft_listadd_back(&newl, elem);
		lst = lst->next;
	}
	return (newl);
}

/*#include<stdio.h>

void	*duplicate_content(void *content)
{
	return (ft_strdup((char *)content));
}

// Function to delete a string
void	delete_content(void *content)
{
	free(content);
}

int	main(void)
{
	// Create a linked list with some strings
	t_list *lst = ft_lstnew("Hello");
	ft_listadd_back(&lst, ft_lstnew("world"));
	ft_listadd_back(&lst, ft_lstnew("from"));
	ft_listadd_back(&lst, ft_lstnew("Linked"));
	ft_listadd_back(&lst, ft_lstnew("List"));

	// Apply ft_lstmap to duplicate the strings
	t_list *duplicated_lst = ft_lstmap(lst, duplicate_content, delete_content);

	// Print the original list
	printf("Original List:\n");
	t_list *current = lst;
	while (current != NULL)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}

	// Print the duplicated list
	printf("\nDuplicated List:\n");
	current = duplicated_lst;
	while (current != NULL)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}

	// Free the memory allocated for the lists
	ft_lstclear(&lst, free);
	ft_lstclear(&duplicated_lst, free);

	return (0);
}*/
