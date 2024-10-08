/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:02:42 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/20 12:05:01 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	if (!d && !s)
		return (NULL);
	if (d == s)
		return (d);
	while (n--)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
// #include<stdio.h>
//  #include<string.h>
/*int main ()
{
   int str[9] ={1,2,3};
   int ptr[2]={1,1,1};
   char *src = "NIGGER";
   char dest[3];
   char *result = ft_memcpy(NULL, NULL, 5);//src + 3, src, 3);

   //printf("%s\n", src);
   printf("%s\n", result);
}*/
// #include <stdio.h>
//  #include <string.h>

// int main()
//  {
// 	//00100001 10101010 11110000 00000101
//  	int a = 458785;  
				// 00000000.000001110000000000100001//
//  	int b = 99658248; // 00000101.111100001010101000001000 
		//00001000 10101010 11110000 00000101
//  	//printf("value of a: %d\n", (int)s);
//  	int *c = ft_memcpy(&a, &b, 3);
//  	printf("%d\n", *c);
//  }
/*int main()
{
	char str[] = "Hello";
	ft_memmove(str + 1, str, 3);
	//memcpy(str + 1, str, 11);
	printf("str = %s\n", str);
}*/
