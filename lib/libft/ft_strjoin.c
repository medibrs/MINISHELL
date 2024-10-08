/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:58:09 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/17 12:09:00 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total;
	char	*copy;

	if (!s1 || !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	total = ft_strlen(s1) + ft_strlen(s2) + 1;
	copy = (char *)malloc(total);
	if (!s1 || !s2 || !copy)
		return (NULL);
	ft_strlcpy(copy, s1, total);
	ft_strlcat(copy, s2, total);
	return (copy);
}
/*
int main ()
{
	char s1[] = "bahae";
	char *s2 = NULL;

	printf("%s", ft_strjoin(s1, s2));
}*/
