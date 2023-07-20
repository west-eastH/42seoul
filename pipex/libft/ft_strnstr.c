/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:00:15 by dongseo           #+#    #+#             */
/*   Updated: 2023/03/27 17:24:12 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j]
			&& i + j < len && haystack[i + j] && needle[j])
			j++;
		if (needle[j] == 0)
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int main ()
{
	char * empty = (char*)"";
	printf("strnstr ---> %s\n", strnstr(empty, empty, 2));
	printf("ft_strnstr ---> %s\n", ft_strnstr(empty, empty, 2));
	printf("strnstr ---> %s\n", strnstr(empty, "", 0));
	printf("ft_strnstr ---> %s\n", ft_strnstr(empty, "", 0));
	return 0;
}
*/