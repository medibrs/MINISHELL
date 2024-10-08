/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:28:48 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/20 17:08:53 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	long long	r;
	int			sign;

	i = 0;
	r = 0;
	sign = 1;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + str[i] - '0';
		i++;
	}
	if (r > 9223372036854775807 && sign == -1)
		return (0);
	if (r < -9223372036854775807 && sign == 1)
		return (-1);
	return (r * sign);
}

/*int main(void)
{
	//char *str = "-99999";
	char *str = "92233720368547758071";
	int result = ft_atoi(str);
	int result1 = atoi(str);

	printf("Result: %d\n", result);

	printf("Result: %d\n", result1);
	return (0);
}*/
