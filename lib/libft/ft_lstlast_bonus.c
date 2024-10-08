/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:05:30 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/17 07:59:23 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_listlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

/*#include<stdio.h>
int main ()
{
    t_list *node1 = ft_lstnew(1);
    t_list *node2 = ft_lstnew(2);
    t_list *node3 = ft_lstnew(3);

    node1->next = node2;
    node2->next = node3;

    t_list *lastnode = ft_listlast(node1);

    if (lastnode)
    {
        printf("Data of the last node : %d\n", lastnode -> data);
    }

    free(node1);
    free(node2);
    free(node3);
}*/
