/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:33:43 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/19 12:57:33 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	lilen;

	i = 0;
	lilen = ft_strlen(little);
	if (*little == 0 || (big == 0 && len == 0))
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (big[i] == *little && len - i >= lilen && ft_strncmp(&big[i], little,
				lilen) == 0)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*b;
	char	*l;

	b = NULL;
	l = NULL;
	printf("%s\n", ft_strnstr(b, l, 0));
	//printf("%s\n", strnstr(b, l , 0));
}*/
