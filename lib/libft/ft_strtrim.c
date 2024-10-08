/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:15:31 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/17 12:04:55 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_isset(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	if (end <= 0)
		return (ft_substr(s1, start, 0));
	while (s1[end] && ft_isset(s1[end], set))
		end--;
	return (ft_substr(s1, start, (end - start + 1)));
}

/*#include<stdio.h>
int main ()
{
	char *s1 = "  bahae  ";
	char *set = " ";

	printf("%s", ft_strtrim(s1, set));
}*/
