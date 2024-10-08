/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 07:47:01 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/17 07:57:45 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst && f)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*void func(void *ptr)
{
	char	*str;

    str = (char*)ptr;
    printf("%s\n", str);
}

int	main(void)
{
    t_list l1;
    l1.content = "qse";

    t_list *l2;
    l2 = malloc(sizeof(t_list));
    l2->content = "abc";



    // t_list *list = calloc(1, sizeof(t_list));
    // t_list *tmp = list;
    // char *str[] = {"abc", "def", "ghi", "jkl", NULL};
    // int i = 0;
    // while(str[i])
    // {
    //     tmp->content = str[i];
    //     tmp->next = calloc(1, sizeof(t_list));
    //     tmp = tmp->next;        
    //     i++;
    // }
    // ft_lstiter(list, func);
    // tmp = list;
    // i = 0;
    // while(tmp)
    // {
    //     printf("%d: %s\n",i,  (char*)tmp->content);
    //     tmp = tmp->next;
    //     // i++;
    // }

}*/
