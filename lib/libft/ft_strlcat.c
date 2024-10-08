/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:25:54 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/20 17:11:55 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ismin(size_t a, size_t b)
{
	while (a < b)
		return (a);
	return (b);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;
	size_t	dstlen;
	size_t	result;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	result = srclen + ismin(dstlen, size);
	if (size <= dstlen)
		return (size + srclen);
	if (!dst || !src || size == 0)
		return (0);
	while (src[i] && dstlen + i < size - 1)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (result);
}

/*int	main(void)
{
	char s[] = "bahaeddine";
	char d[] = "mestini";

	printf("%ld", ft_strlcat(d, s, 19));
	printf("%s", d);
}*/
