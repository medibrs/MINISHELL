/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:50:35 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 23:30:31 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	slen;

	i = 0;
	slen = ft_strlen((char *)src);
	if (size == 0)
		return (slen);
	if (size)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	return (slen);
}

/*int	main(void)
{
	char	d[999];
	char	s[];

	s[] = "bahaeddine";
	printf("%ld me", ft_strlcpy(d, s, 5));
}*/
