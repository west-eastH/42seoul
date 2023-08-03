/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:06:59 by dongseo           #+#    #+#             */
/*   Updated: 2023/03/28 14:18:03 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (c >= 256)
		c %= 256;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		i++;
	}
	if (s[i] == c)
		return ((char *)s + i);
	else
		return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int main ()
{
	char *s1 = "abcvvvv";
	char *s2 = "abcvvvv";
	char *s3 = "";
	char *s4 = "";

	printf("%s\n", strchr(s1, 'w' + 256));
	printf("%s\n", ft_strchr(s2, 'w' + 256));
	printf("%s\n", strchr(s3, 98));
	printf("%s\n", ft_strchr(s4, 98));
	return 0;
}
*/