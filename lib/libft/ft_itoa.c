/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:24:30 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/20 15:17:20 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nlen(int n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
	{
		count++;
		n = -n;
	}
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*copy;
	int		numlen;
	long	nb;
	int		j;

	j = 0;
	numlen = nlen(n);
	copy = (char *)malloc((numlen + 1) * sizeof(char));
	if (!copy)
		return (0);
	nb = n;
	copy[numlen] = '\0';
	if (nb < 0)
	{
		copy[0] = '-';
		nb = -nb;
		j = 1;
	}
	numlen--;
	while ((numlen >= 0 && j == 0) || (numlen > 0 && j == 1))
	{
		copy[numlen--] = nb % 10 + 48;
		nb /= 10;
	}
	return (copy);
}

// int	main(void) {
// 	char c;

// 	// while ((c = getchar()) != EOF) {
// 	// 	//Process each character
// 	// 	putchar(c);
// 	// }

// 	printf("\nEOF detected. End of input%d .\n", EOF);

// 	return (0);
// }
