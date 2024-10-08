/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:27:22 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/15 10:55:23 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = s;
	while (i < n)
	{
		p[i] = c;
		i++;
	}
	return (p);
}

// int main ()
// {
// 	char s[] = "tati";
// 	printf("%s", ft_memset(s, 'a', 4));
// }
// int main()
// {
// 	int arr[] = {4, 5, 9};

// 	printf("%d\n", arr[0]);

// }