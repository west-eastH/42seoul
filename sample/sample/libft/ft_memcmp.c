/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:27:39 by dongseo           #+#    #+#             */
/*   Updated: 2023/03/27 17:23:07 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			i;

	if (n == 0)
		return (0);
	i = 0;
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (ptr1[i] == ptr2[i] && i + 1 < n)
		i++;
	return (ptr1[i] - ptr2[i]);
}

/*
#include <stdio.h>
#include <string.h>

int main ()
{
	char *s1 = "zabcddefgss";
	char *s2 = "abczdefgss";
	
	printf("strncmp --> %d\n", memcmp(s1, s2, 6));
	printf("ft_strncmp --> %d\n", ft_memcmp(s1, s2, 6));
	return 0;
}
*/