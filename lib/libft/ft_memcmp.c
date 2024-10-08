/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:46:48 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/15 12:55:01 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s11;
	unsigned char	*s22;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	i = 0;
	while (n--)
	{
		if (s11[i] != s22[i])
			return (s11[i] - s22[i]);
		i++;
	}
	return (0);
}

// int main () {
//    int str1 = 123;
//    int str2 = 123;
//    int i;

//    //memcpy(str1, "abcdef", 6);
//    //memcpy(str2, "\0", 6);

//    i = ft_memcmp(&str1, &str2, sizeof(str1));

//    if(i > 0) {
//       printf("str2 is less than str1");
//    } else if(i < 0) {
//       printf("str1 is less than str2");
//    } else {
//       printf("str1 is equal to str2");
//    }

//    return(0);
// }
// #include <stdio.h>
// int main ()
// {
// 	char *s1 = "oahae";
// 	char *s2 = "cahae";

// 	printf("%d", ft_memcmp(s1, s2, 5));
// 	printf("%d", memcmp(s1, s2, 5));
// }
