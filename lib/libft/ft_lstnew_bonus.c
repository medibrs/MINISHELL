/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 07:22:17 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/17 20:41:43 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->content = content;
	return (new_node);
}

// void del (void *content)
// {
// 	free(content);
// }

// int main ()
// {
// 	t_list *node = ft_lstnew("bahae");
// 	ft_listadd_back(&node, ft_lstnew("mestini"));
// 	ft_listadd_back(&node , ft_lstnew("ok"));

// 	t_list *current = node;
// 	while(current)
// 	{
// 		printf("%s\n", (char *)current ->content);
// 		current = current ->next;
// 	}
// 	int Sresult = ft_lstsize(node);
// 	printf("%d", Sresult);
// 	//ft_lstclear(&node, del);

// }

/*int main()
{
	t_list *first = ft_lstnew("first");
	if (!first)
		return (1);
	t_list *snd = ft_lstnew("second");
	t_list *thd = ft_lstnew("third");

	if (snd == NULL || thd == NULL)
	{
		free(first);
		free(snd);
		free(thd);
	}

	first -> next = snd;
	snd -> next = thd;
	t_list *current = first;
	while (current != NULL)
	{
		printf("your content is :%s\n", current->content);
		current = current->next;
	}
	t_list *tmp;

	while(current)
	{
		tmp  = current;
		free(tmp);
		current = current->next;
	}
	return (0);
}*/
