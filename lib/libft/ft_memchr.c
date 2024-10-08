/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:35:04 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/17 14:38:10 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

/*#include <stdio.h>

int	main(void) {
	const char *test_string = "Hello, World!";
	char search_char = 'l';
	size_t search_length = 3;

	char *result1 = ft_memchr(test_string, search_char, search_length);
	char *result2 = memchr(test_string,search_char,search_length);
	printf("me '%s'\n", result1);
	printf("not me '%s'", result2);
}*/
