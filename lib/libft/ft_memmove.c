/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:16:19 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/09 17:16:22 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dest;
	s = src;
	if (!d && !s)
		return (NULL);
	if (d == s)
		return (d);
	if (d < s)
		ft_memcpy(d, s, n);
	else
	{
		while (n--)
			*(d + n) = *(s + n);
	}
	return (dest);
}

/*#include<stdio.h>
#include<string.h>
int main ()
{
	char dest[6];
	char src[] = "bahaeddine";

	char *result = ft_memmove("hello", "hello", 8);

	printf("%s", result);
}*/