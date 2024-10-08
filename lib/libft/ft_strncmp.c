/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:03:43 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 23:30:13 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
	{
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// #include <stdio.h>
// int main ()
// {
// 	char *s1 = "oahae";
// 	char *s2 = "cahae";

// 	printf("%d", ft_strncmp(s1, s2, 5));
// 	printf("%d", strncmp(s1, s2, 5));
// }
