/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:58:14 by bmestini          #+#    #+#             */
/*   Updated: 2023/11/17 18:02:59 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wc(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

static char	*gw(const char *s, unsigned int *i1, char c)
{
	int		i;
	char	*copy;
	int		wl;

	wl = 0;
	while (s[*i1] && s[*i1] == c)
		(*i1)++;
	i = *i1;
	while (s[i] && s[i] != c)
	{
		wl++;
		i++;
	}
	copy = malloc(sizeof(char) * (wl + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (s[*i1] && s[*i1] != c)
	{
		copy[i] = s[*i1];
		(*i1)++;
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static char	**err(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char			**copy;
	unsigned int	i;
	unsigned int	i1;
	unsigned int	wc1;

	i = 0;
	i1 = 0;
	if (!s)
		return (NULL);
	wc1 = wc(s, c);
	copy = malloc(sizeof(char *) * (wc1 + 1));
	if (!copy)
		return (NULL);
	while (i < wc1)
	{
		copy[i] = gw(s, &i1, c);
		if (!copy[i])
			return (err(copy));
		i++;
	}
	copy[i] = 0;
	return (copy);
}

// #include<stdio.h>
// int main ()
// {
// 	char *s = ",,,,bahae,is,,a ok,,";
// 	char c = ',';	
// 	//char **splitted = 
// 	ft_split(NULL, c);
// 	int i = 0;
	// while(splitted[i] != NULL)
	// {
	// 	printf("value : %s\n", splitted[i]);
	// 	i++;
	// }
//}
