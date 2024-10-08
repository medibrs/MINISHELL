/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:57:33 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/17 14:56:35 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_listadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst && !new)
		return ;
	last = *lst;
	if (*lst)
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*lst = new;
}

// void del(void *content)
// {
// 	free(content);
// }

// int main ()
// {
// 		t_list *lst = ft_lstnew(ft_strdup("bahae"));
// 	ft_listadd_back(&lst, ft_lstnew(ft_strdup("mestini")));
// 	ft_listadd_back(&lst, ft_lstnew(ft_strdup("mok")));
// 	ft_lstadd_front(&lst, ft_lstnew(ft_strdup("kys")));
// 	t_list *current = lst;
// 	// while(current)
// 	// {
// 	// 	printf("%s", (char *)current->content);
// 	// 	current = current -> next;
// 	// }
// 	int size = ft_lstsize(lst);
// 	printf("%s\n", lst->next->content);
// 	printf("%d\n", size);

// 	ft_lstclear(&lst, &del);
// }