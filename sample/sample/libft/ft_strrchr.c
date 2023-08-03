/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:06:59 by dongseo           #+#    #+#             */
/*   Updated: 2023/03/27 17:24:15 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*res;
	size_t	len;

	if (c >= 256)
		c %= 256;
	len = ft_strlen(s);
	res = NULL;
	i = 0;
	while (i <= len)
	{
		if (s[i] == c)
			res = ((char *)s + i);
		i++;
	}
	return (res);
}

/* 
#include <stdio.h>
#include <string.h>

int main ()
{
	char *s1 = "abcvvvvaa";
	char *s2 = "abcvvvvaa";
	char *s3 = "";
	char *s4 = "";

	printf("%s\n", strrchr(s1, 0));
	printf("%s\n", ft_strrchr(s2, 0));
	printf("%s\n", strrchr(s3, 0));
	printf("%s\n", ft_strrchr(s4, 0));
	return 0;
}
 */