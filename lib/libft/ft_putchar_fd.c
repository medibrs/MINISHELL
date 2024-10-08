/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:24:23 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/16 20:25:46 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

/*#include <fcntl.h>
int main()
{
	int fd = open("haha", O_RDWR | O_CREAT | O_TRUNC, 0644);
	ft_putchar_fd('5', fd);
	close (fd);
	ft_putchar_fd('l', 1);
}*/
