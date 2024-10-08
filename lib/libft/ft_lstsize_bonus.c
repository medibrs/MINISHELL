/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 10:30:53 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/15 10:36:23 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

/*#include<stdio.h>
int	main(void)
{
	t_list *node1 = ft_lstnew(1);
	t_list *node2 = ft_lstnew(2);
	t_list *node3 = ft_lstnew(3);

	node1->next = node2;
	node2->next = node3;

	int size = ft_lstsize(node1);
}*/
