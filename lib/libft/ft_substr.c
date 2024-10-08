/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:05:22 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/20 12:05:32 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*copy;
	size_t	slen;

	i = 0;
	if (!s)
		return (0);
	slen = ft_strlen((char *)s);
	if (len > slen - start)
		len = slen - start;
	if ((size_t)start >= slen)
		return (ft_strdup(""));
	copy = (char *)ft_calloc((len + 1), sizeof(char));
	if (!copy || s == 0)
		return (NULL);
	while (s[start] && len--)
		copy[i++] = s[start++];
	return (copy);
}

/*int main()
{
	char *str = ft_substr(NULL, 12, 5);
	printf("%s\n", str);
}*/
