/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 08:52:45 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/14 17:48:20 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

/*#include <stdio.h>
int	main(void) {
    t_list *head = NULL;

    t_list *newNode1 = ft_lstnew("Node 1");
    t_list *newNode2 = ft_lstnew("Node 2");
    t_list *newNode3 = ft_lstnew("Node 3");

    newNode1 ->next = newNode2;
    newNode2 ->next = newNode3;

    ft_lstadd_front(&head, newNode1);
    ft_lstadd_front(&head, newNode3);
    ft_lstadd_front(&head, newNode2);

    // Print the contents of the list
    t_list *current = head;
    while (current != NULL) {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }




    printf("%p\n", newNode2);
    printf("%p\n", newNode3);
    printf("%p\n", newNode1);
    printf("%p\n", head);
    
    return (0);
}*/
